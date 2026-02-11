handle_getpubkey(struct ntb_keyring *keyring,
                 struct ntb_blob *blob)
{
        const uint8_t *ripe_or_tag;
        uint64_t nonce;
        int64_t timestamp;
        uint64_t address_version;
        ssize_t header_length;
        uint64_t stream_number;

        header_length = ntb_proto_get_command(blob->data,
                                              blob->size,

                                              NTB_PROTO_ARGUMENT_64,
                                              &nonce,

                                              NTB_PROTO_ARGUMENT_TIMESTAMP,
                                              &timestamp,

                                              NTB_PROTO_ARGUMENT_VAR_INT,
                                              &address_version,

                                              NTB_PROTO_ARGUMENT_VAR_INT,
                                              &stream_number,

                                              NTB_PROTO_ARGUMENT_END);

        if (header_length == -1) {
                ntb_log("Invalid getpubkey message received");
                return;
        }

        if (address_version < 2 || address_version > 4) {
                ntb_log("getpubkey with unsupported address version "
                        "%" PRIu64 " received",
                        address_version);
                return;
        }

        ripe_or_tag = blob->data + header_length;

        if (address_version < 4) {
                if (blob->size - header_length < RIPEMD160_DIGEST_LENGTH) {
                        ntb_log("Invalid getpubkey message received");
                        return;
                }

                handle_getpubkey_with_ripe(keyring,
                                           address_version,
                                           stream_number,
                                           ripe_or_tag);
        } else {
                if (blob->size - header_length < NTB_ADDRESS_TAG_SIZE) {
                        ntb_log("Invalid getpubkey message received");
                        return;
                }

                handle_getpubkey_with_tag(keyring,
                                          address_version,
                                          stream_number,
                                          ripe_or_tag);
        }
}
