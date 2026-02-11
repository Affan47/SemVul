config_metadata(const char *name, const char *version, const char *desc_short,
                const char *desc_long, pe_cluster_option * option_list, int len)
{
    int lpc = 0;

    fprintf(stdout, "<?xml version=\"1.0\"?>"
            "<!DOCTYPE resource-agent SYSTEM \"ra-api-1.dtd\">\n"
            "<resource-agent name=\"%s\">\n"
            "  <version>%s</version>\n"
            "  <longdesc lang=\"en\">%s</longdesc>\n"
            "  <shortdesc lang=\"en\">%s</shortdesc>\n"
            "  <parameters>\n", name, version, desc_long, desc_short);

    for (lpc = 0; lpc < len; lpc++) {
        if (option_list[lpc].description_long == NULL && option_list[lpc].description_short == NULL) {
            continue;
        }
        fprintf(stdout, "    <parameter name=\"%s\" unique=\"0\">\n"
                "      <shortdesc lang=\"en\">%s</shortdesc>\n"
                "      <content type=\"%s\" default=\"%s\"/>\n"
                "      <longdesc lang=\"en\">%s%s%s</longdesc>\n"
                "    </parameter>\n",
                option_list[lpc].name,
                option_list[lpc].description_short,
                option_list[lpc].type,
                option_list[lpc].default_value,
                option_list[lpc].description_long ? option_list[lpc].
                description_long : option_list[lpc].description_short,
                option_list[lpc].values ? "  Allowed values: " : "",
                option_list[lpc].values ? option_list[lpc].values : "");
    }
    fprintf(stdout, "  </parameters>\n</resource-agent>\n");
}
