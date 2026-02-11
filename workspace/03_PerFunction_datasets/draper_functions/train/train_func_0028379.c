xml_util_get_child_element_content_url (xmlNode    *node,
                                        const char *child_name,
                                        SoupURI    *base)
{
        SoupURI *uri;
        char *url;

        uri = xml_util_get_child_element_content_uri (node, child_name, base);
        if (!uri)
                return NULL;

        url = soup_uri_to_string (uri, FALSE);

        soup_uri_free (uri);

        return url;
}
