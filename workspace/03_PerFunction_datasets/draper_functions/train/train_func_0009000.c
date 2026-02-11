json_creds(krb5_context context, krb5_creds *creds, k5_json_value *val_out)
{
    krb5_error_code ret;
    k5_json_array array;
    k5_json_value client = NULL, server = NULL, keyblock = NULL, addrs = NULL;
    k5_json_value authdata = NULL;

    *val_out = NULL;
    ret = json_principal(context, creds->client, &client);
    if (ret)
        goto cleanup;
    ret = json_principal(context, creds->server, &server);
    if (ret)
        goto cleanup;
    ret = json_keyblock(&creds->keyblock, &keyblock);
    if (ret)
        goto cleanup;
    ret = json_addresses(creds->addresses, &addrs);
    if (ret)
        goto cleanup;
    ret = json_authdata(creds->authdata, &authdata);
    if (ret)
        goto cleanup;

    ret = k5_json_array_fmt(&array, "vvviiiibivBBv", client, server, keyblock,
                            creds->times.authtime, creds->times.starttime,
                            creds->times.endtime, creds->times.renew_till,
                            creds->is_skey, creds->ticket_flags, addrs,
                            (void *)creds->ticket.data,
                            (size_t)creds->ticket.length,
                            (void *)creds->second_ticket.data,
                            (size_t)creds->second_ticket.length, authdata);
    if (ret)
        goto cleanup;
    *val_out = array;

cleanup:
    k5_json_release(client);
    k5_json_release(server);
    k5_json_release(keyblock);
    k5_json_release(addrs);
    k5_json_release(authdata);
    return ret;
}
