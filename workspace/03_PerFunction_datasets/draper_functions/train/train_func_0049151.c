response(List *push_headers, Octstr **username, Octstr **password)
{
    Octstr *header_value,
           *basic;
    size_t basic_len;
    List *auth_list;

    *username = NULL;
    *password = NULL;

    if ((header_value = http_header_find_first(push_headers,
            "Authorization")) == NULL)
        goto no_response3;

    octstr_strip_blanks(header_value);
    basic = octstr_imm("Basic");
    basic_len = octstr_len(basic);

    if (octstr_ncompare(header_value, basic, basic_len) != 0)
        goto no_response1;

    octstr_delete(header_value, 0, basic_len);
    octstr_strip_blanks(header_value);
    octstr_base64_to_binary(header_value);
    auth_list = octstr_split(header_value, octstr_imm(":"));

    if (gwlist_len(auth_list) != 2)
        goto no_response2;

    *username = octstr_duplicate(gwlist_get(auth_list, 0));
    *password = octstr_duplicate(gwlist_get(auth_list, 1));

    if (username == NULL) {
        goto no_response2;
    }

    if (password == NULL) {
        goto no_response4;
    }

    debug("wap.push.ppg.pushuser", 0, "we have an username and a password in"
          " authorization header");
    gwlist_destroy(auth_list, octstr_destroy_item);
    octstr_destroy(header_value);
    http_header_remove_all(push_headers, "Authorization");
    return HEADER_AUTHENTICATION;

no_response1:
    octstr_destroy(header_value);
    return NO_USERNAME;

no_response2:
    gwlist_destroy(auth_list, octstr_destroy_item);
    octstr_destroy(header_value);
    return NO_USERNAME;

no_response3:
    return NO_USERNAME;

no_response4:
    gwlist_destroy(auth_list, octstr_destroy_item);
    octstr_destroy(header_value);
    return NO_PASSWORD;
}
