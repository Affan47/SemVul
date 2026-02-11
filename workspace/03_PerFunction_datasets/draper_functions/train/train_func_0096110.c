for_each_outgoing_cb(const struct ntb_store_outgoing *outgoing,
                     void *user_data)
{
        struct ntb_keyring *keyring = user_data;
        struct ntb_keyring_message *message;
        struct ntb_key *from_key;
        char from_address_string[NTB_ADDRESS_MAX_LENGTH + 1];

        if (outgoing->content_id >= keyring->next_message_content_id)
                keyring->next_message_content_id = outgoing->content_id + 1;

        from_key = get_private_key_for_address(keyring,
                                               &outgoing->from_address);
        if (from_key == NULL) {
                ntb_address_encode(&outgoing->from_address,
                                   from_address_string);
                ntb_log("Skipping saved message from %s because the private "
                        "key is no longer available",
                        from_address_string);
                return;
        }

        message = create_message(keyring,
                                 from_key,
                                 &outgoing->to_address,
                                 outgoing->content_encoding,
                                 outgoing->content_id);

        message->last_getpubkey_send_time = outgoing->last_getpubkey_send_time;
        message->last_msg_send_time = outgoing->last_msg_send_time;
        memcpy(message->ackdata, outgoing->ackdata, NTB_PROTO_ACKDATA_SIZE);

        if (message->to_key == NULL)
                load_public_key_for_message(message);
        else
                post_message(message);
}
