helper_curl_easy_setopt(value conn, value option)
{
    CAMLparam2(conn, option);
    CAMLlocal1(data);
    Connection *connection = (Connection *)Field(conn, 0);

    checkConnection(connection);

    if (Is_long(option))
    {
        char error[128];

        sprintf(error, "Unimplemented Option: %s",
                findOption(unimplementedOptionMap,
                           (CURLoption)(Long_val(option))));

        failwith(error);
    }

    if (!Is_block(option))
        failwith("Not a block");

    if (Wosize_val(option) < 1)
        failwith("Insufficient data in block");

    data = Field(option, 0);

    if (Tag_val(option) < sizeof(implementedOptionMap)/sizeof(CURLOptionMapping))
        (*implementedOptionMap[Tag_val(option)].optionHandler)(connection,
                                                               data);
    else
        failwith("Invalid CURLOPT Option");

    CAMLreturn0;
}
