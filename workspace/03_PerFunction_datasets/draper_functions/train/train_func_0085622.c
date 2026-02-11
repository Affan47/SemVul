send_request(const char* p) {
    char buf[100000];
    sprintf(buf,
        "<boinc_gui_rpc_request>\n"
        "%s"
        "</boinc_gui_rpc_request>\n\003",
        p
    );
    int n = send(sock, buf, (int)strlen(buf), 0);
    if (n < 0) {


        return ERR_WRITE;
    }
    return 0;
}
