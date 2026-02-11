soap_send(PrivData* privdata, Octstr* xmlbuffer, Msg* msg)
{
    List *requestHeaders;
    Octstr* postdata;


    requestHeaders = http_create_empty_headers();
    http_header_add(requestHeaders, "User-Agent", "Kannel " GW_VERSION);

    if (privdata->form_urlencoded) {
        http_header_add(requestHeaders, "Content-Type", "application/x-www-form-urlencoded");
        postdata = octstr_format("%S=%E", privdata->form_variable, xmlbuffer);
    } else {
        http_header_add(requestHeaders, "Content-Type", "multipart/form-data, boundary=AaB03x");
        postdata = octstr_format("--AaB03x\r\n"
                                 "content-disposition: form-data; name=\"%S\"\r\n\r\n%S",
                                 privdata->form_variable, xmlbuffer);
    }


    soap_client_init_query(privdata, requestHeaders, postdata, msg);

    O_DESTROY(postdata);


    http_destroy_headers(requestHeaders);

    return;

}
