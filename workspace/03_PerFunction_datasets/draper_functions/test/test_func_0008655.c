gupnp_xml_doc_new (xmlDoc *xml_doc)
{
        GUPnPXMLDoc *doc;

        g_return_val_if_fail (xml_doc != NULL, NULL);

        doc = g_object_new (GUPNP_TYPE_XML_DOC, NULL);

        doc->doc = xml_doc;

        return doc;
}
