oisd_send_response(struct packet *request, PrivData *pdata)
{
    struct packet *response;

    gw_assert(request != NULL);
    gw_assert(request->operation < RESPONSE);

    response = packet_create(request->operation + RESPONSE, request->opref);

    octstr_append_char(response->data, (char) RESULT_SUCCESS);

    packet_set_data_size(response);

    debug("bb.sms.oisd", 0, "OISD[%s]: sending response",
          octstr_get_cstr(pdata->conn->id));
    octstr_dump(response->data, 0);


    octstr_write_to_socket(pdata->socket, response->data);

    packet_destroy(response);
}
