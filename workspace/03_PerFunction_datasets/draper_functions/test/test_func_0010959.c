colors_load(const char* filename)
{
    xmlDocPtr xfile;
    xmlNodePtr xroot;

    if (!g_file_test(filename, G_FILE_TEST_EXISTS)) return FALSE;


    xfile = xmlParseFile(filename);
    if (!xfile) return FALSE;

    xroot = xmlDocGetRootElement(xfile);
    if (xroot == NULL)
    {
        g_log("COLOR", G_LOG_LEVEL_WARNING, "no root element in file: %s", filename);
        xmlFreeDoc(xfile);
        return FALSE;
    }

    if (strcmp(xroot->name, "Colors"))
    {
        g_log("COLOR", G_LOG_LEVEL_WARNING, "Root element != 'Colors'");
        xmlFreeDoc(xfile);
        return FALSE;
    }

    xml_colors_get(xfile, xroot);

    xmlFreeDoc(xfile);

    return TRUE;
}
