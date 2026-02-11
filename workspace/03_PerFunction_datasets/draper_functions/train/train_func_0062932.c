xml_xpath_init(xmlDocPtr document) {
    xml_xpath_t *result = malloc(sizeof(xml_xpath_t));
    if (result == NULL)
        return NULL;

    result->document = document;
    result->xpath_ctx = xmlXPathNewContext(result->document);
    if(result->xpath_ctx == NULL) {
        xmlFreeDoc(result->document);
        free(result);
        return NULL;
    }
    result->context = NULL;

    return result;
}
