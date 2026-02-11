do_rpc(ACCOUNT_IN& ai) {
    int retval;
    string url;
    string parameter;

    url = ai.url;
    canonicalize_master_url(url);

    url += "create_account.php?email_addr=";
    parameter = ai.email_addr;
    escape_url(parameter);
    url += parameter;

    url += "&passwd_hash=";
    parameter = ai.passwd_hash;
    escape_url(parameter);
    url += parameter;

    url += "&user_name=";
    parameter = ai.user_name;
    escape_url(parameter);
    url += parameter;

    if (!ai.team_name.empty()) {
        url += "&team_name=";
        parameter = ai.team_name;
        escape_url(parameter);
        url += parameter;
    }
    retval = gui_http->do_rpc(
        this, url.c_str(), CREATE_ACCOUNT_FILENAME, false
    );
    if (retval) {
        error_num = retval;
    } else {
        error_num = ERR_IN_PROGRESS;
    }
    return retval;
}
