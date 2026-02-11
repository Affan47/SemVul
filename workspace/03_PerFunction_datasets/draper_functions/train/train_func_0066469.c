xmlRelaxNGFreeTypeLibrary(xmlRelaxNGTypeLibraryPtr lib,
                          const xmlChar * namespace ATTRIBUTE_UNUSED)
{
    if (lib == NULL)
        return;
    if (lib->namespace != NULL)
        xmlFree((xmlChar *) lib->namespace);
    xmlFree(lib);
}
