get_file_xml(
    const char* file_name, vector<const char*> urls,
    double max_nbytes,
    double report_deadline,
    bool generate_upload_certificate,
    R_RSA_PRIVATE_KEY& key,
    char* out
) {
    char buf[8192];
    sprintf(out,
        "<app>\n"
        "    <name>file_xfer</name>\n"
        "</app>\n"
        "<app_version>\n"
        "    <app_name>file_xfer</app_name>\n"
        "    <version_num>0</version_num>\n"
        "</app_version>\n"
        "<file_info>\n"
        "    <name>%s</name>\n"
        "    <max_nbytes>%.0f</max_nbytes>\n",
        file_name,
        max_nbytes
    );
    for (unsigned int i=0; i<urls.size(); i++) {
        sprintf(buf, "    <url>%s</url>\n", urls[i]);
        strcat(out, buf);
    }
    sprintf(buf,
        "</file_info>\n"
        "<workunit>\n"
        "    <name>upload_%s</name>\n"
        "    <app_name>file_xfer</app_name>\n"
        "</workunit>\n"
        "<result>\n"
        "    <wu_name>upload_%s</wu_name>\n"
        "    <name>upload_%s</name>\n"
        "    <file_ref>\n"
        "        <file_name>%s</file_name>\n"
        "    </file_ref>\n"
        "    <report_deadline>%f</report_deadline>\n"
        "</result>\n",
        file_name,
        file_name,
        file_name,
        file_name,
        report_deadline
    );
    strcat(out, buf);
    if (generate_upload_certificate) {
        add_signatures(out, key);
    }
    return 0;
}
