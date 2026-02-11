verify_didl_attributes (xmlNode *node)
{
        const char *content;

        content = xml_util_get_child_element_content (node, "date");
        if (content) {

                char *ptr = (char *) content;
                int state = 0;
                while (*ptr) {
                        if (state == 4 || state == 7) {
                                if (*ptr != '-')
                                        return FALSE;
                        } else {
                                if (!isdigit (*ptr))
                                        return FALSE;
                        }

                        ptr++;
                        state++;
                        if (state == 10)
                                break;
                }
        }

        return xml_util_verify_attribute_is_boolean (node, "restricted");
}
