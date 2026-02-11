emi_open_session(SMSCenter *smsc)
{
    char message_whole  [1024];
    char message_body   [1024];
    char message_header [50];
    char message_footer [10];
    char my_buffer      [1024];
    int length;

    memset(message_whole,  0, sizeof(message_whole));
    memset(message_body,   0, sizeof(message_body));
    memset(message_header, 0, sizeof(message_header));
    memset(message_footer, 0, sizeof(message_footer));

    if (emi_fill_ucp60_login(message_body, smsc->emi_username, smsc->emi_password) < 0) {
        error(0, "emi_fill_ucp60_login failed");
        return -1;
    }

    length = strlen(message_body);
    length += 13;
    length += 2;
    length += 2;

    sprintf(message_header, "%02i/%05i/O/60",
            (smsc->emi_current_msg_number++ % 100), length);


    sprintf(my_buffer, "%s/%s/", message_header, message_body);
    generate_checksum((unsigned char *)my_buffer, (unsigned char *)message_footer);

    sprintf(message_whole, "\x02%s/%s/%s\x03", message_header,
            message_body, message_footer);

    debug("bb.sms.emi", 0, "final UCP60 msg: <%s>", message_whole);

    put_data(smsc, message_whole, strlen(message_whole), 0);

    if (!wait_for_ack(smsc, 60)) {
	info(0, "emi_open_session: wait for ack failed!");
	return -1;
    }

    return 0;
}
