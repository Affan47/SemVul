write(MIOFILE& out) {
    char s5un[2048], s5up[2048], hun[2048], hup[2048];
    xml_escape(socks5_user_name, s5un, sizeof(s5un));
    xml_escape(socks5_user_passwd, s5up, sizeof(s5up));
    xml_escape(http_user_name, hun, sizeof(hun));
    xml_escape(http_user_passwd, hup, sizeof(hup));
    out.printf(
        "<proxy_info>\n"
        "%s"
        "%s"
        "%s"
        "    <socks_server_name>%s</socks_server_name>\n"
        "    <socks_server_port>%d</socks_server_port>\n"
        "    <http_server_name>%s</http_server_name>\n"
        "    <http_server_port>%d</http_server_port>\n"
        "    <socks5_user_name>%s</socks5_user_name>\n"
        "    <socks5_user_passwd>%s</socks5_user_passwd>\n"
        "    <http_user_name>%s</http_user_name>\n"
        "    <http_user_passwd>%s</http_user_passwd>\n"
        "    <no_proxy>%s</no_proxy>\n",
        use_http_proxy?"    <use_http_proxy/>\n":"",
        use_socks_proxy?"    <use_socks_proxy/>\n":"",
        use_http_auth?"    <use_http_auth/>\n":"",
        socks_server_name,
        socks_server_port,
        http_server_name,
        http_server_port,
        s5un,
        s5up,
        hun,
        hup,
        noproxy_hosts
    );
    if (strlen(autodetect_server_name)) {
        out.printf(
            "    <autodetect_protocol>%d</autodetect_protocol>\n"
            "    <autodetect_server_name>%d</autodetect_server_name>\n"
            "    <autodetect_port>%d</autodetect_port>\n",
            autodetect_protocol,
            autodetect_server_name,
            autodetect_port
        );
    }
    out.printf(
        "</proxy_info>\n"
    );
    return 0;
}
