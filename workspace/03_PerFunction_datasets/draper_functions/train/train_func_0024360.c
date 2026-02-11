delayed_http_reply(Msg *msg)
{
    HTTPClient *client;
    Octstr *os, *answer;
    char id[UUID_STR_LEN + 1];
    int status;

    uuid_unparse(msg->ack.id, id);
    os = octstr_create(id);
    debug("sms.http", 0, "Got ACK (%ld) of %s", msg->ack.nack, octstr_get_cstr(os));
    client = dict_remove(client_dict, os);
    if (client == NULL) {
        debug("sms.http", 0, "No client - multi-send or ACK to pull-reply");
        octstr_destroy(os);
        return;
    }


    switch (msg->ack.nack) {
      case ack_success:
        status = HTTP_ACCEPTED;
        answer = octstr_create("0: Accepted for delivery");
        break;
      case ack_buffered:
        status = HTTP_ACCEPTED;
        answer = octstr_create("3: Queued for later delivery");
        break;
      case ack_failed:
        status = HTTP_FORBIDDEN;
        answer = octstr_create("Not routable. Do not try again.");
        break;
      case ack_failed_tmp:
        status = HTTP_SERVICE_UNAVAILABLE;
        answer = octstr_create("Temporal failure, try again later.");
        break;
      default:
	error(0, "Strange reply from bearerbox!");
        status = HTTP_SERVICE_UNAVAILABLE;
        answer = octstr_create("Temporal failure, try again later.");
        break;
    }

    http_send_reply(client, status, sendsms_reply_hdrs, answer);

    octstr_destroy(answer);
    octstr_destroy(os);
}
