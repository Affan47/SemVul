create_msg_blob_cb(struct ntb_blob *blob,
                   void *user_data)
{
        struct ntb_keyring_message *message = user_data;
        struct ntb_keyring *keyring = message->keyring;
        int payload_length_extra_bytes;
        int nonce_trials_per_byte;

        message->crypto_cookie = NULL;

        ntb_blob_unref(message->blob);
        message->blob = ntb_blob_ref(blob);

        ntb_log("Doing proof-of-work calculation for msg");

        message->state = NTB_KEYRING_MESSAGE_STATE_CALCULATING_MSG_POW;


        payload_length_extra_bytes =
                message->to_key->payload_length_extra_bytes;
        if (payload_length_extra_bytes < NTB_PROTO_MIN_EXTRA_BYTES)
                payload_length_extra_bytes = NTB_PROTO_MIN_EXTRA_BYTES;

        nonce_trials_per_byte =
                message->to_key->nonce_trials_per_byte;
        if (nonce_trials_per_byte < NTB_PROTO_MIN_NONCE_TRIALS_PER_BYTE)
                nonce_trials_per_byte = NTB_PROTO_MIN_NONCE_TRIALS_PER_BYTE;

        message->pow_cookie =
                ntb_pow_calculate(keyring->pow,
                                  blob->data + sizeof (uint64_t),
                                  blob->size - sizeof (uint64_t),
                                  payload_length_extra_bytes,
                                  nonce_trials_per_byte,
                                  msg_pow_cb,
                                  message);
}
