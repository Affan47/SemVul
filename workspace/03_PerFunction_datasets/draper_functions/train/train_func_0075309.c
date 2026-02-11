xidris_send_sms(SMSCConn *conn, Msg *sms)
{
    ConnData *conndata = conn->data;
    Octstr *url, *new_msg;
    List *headers;
    int dcs, esm_class;

    url = new_msg = NULL;
    dcs = esm_class = 0;


    url = octstr_format("%S?"
        "app_id=%E&key=%E&dest_addr=%E&source_addr=%E",
        conndata->send_url, conndata->username,
        conndata->password, sms->sms.receiver, sms->sms.sender);

    if (octstr_len(sms->sms.udhdata)) {


        dcs = fields_to_dcs(sms, sms->sms.alt_dcs);


        esm_class = 0x03 | 0x40;


        new_msg = octstr_duplicate(sms->sms.udhdata);
        octstr_append(new_msg, sms->sms.msgdata);

        octstr_format_append(url, "&type=200&dcs=%d&esm=%d&message=%H",
                             dcs, esm_class, new_msg);
    }  else {


        octstr_format_append(url, "&type=%E&message=%E",
                            (sms->sms.mclass ? octstr_imm("1") : octstr_imm("0")),
                            sms->sms.msgdata);
    }


    if (octstr_len(sms->sms.account)) {
        octstr_url_decode(sms->sms.account);
        octstr_format_append(url, "&%s", octstr_get_cstr(sms->sms.account));
    }

    headers = gwlist_create();
    debug("smsc.http.xidris", 0, "HTTP[%s]: Sending request <%s>",
          octstr_get_cstr(conn->id), octstr_get_cstr(url));

    http_start_request(conndata->http_ref, HTTP_METHOD_GET, url, headers,
                       NULL, 0, sms, NULL);

    octstr_destroy(url);
    octstr_destroy(new_msg);
    http_destroy_headers(headers);
}
