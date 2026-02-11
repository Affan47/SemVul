rum_element_set_value(rum_element_t *element, const char *attr_name, const char *attr_value)
{
    int i;
    const char *attr_name2;

    rum_set_error(NULL);


    if (element && element->tag && element->values && attr_name) {


        for (i = 0; i < rum_tag_get_nattrs(element->tag); ++i) {


            if ((attr_name2 = rum_tag_get_attr_name(element->tag, i)) == NULL) {
                return -1;
            }


            if (!strcmp(attr_name, attr_name2)) {


                if (element->values[i] != NULL) {
                    rum_set_error("Attribute may not be specified twice in same element");
                    return -1;
                }


                if ((element->values[i] = xmlcontent2plaintext(attr_value)) == NULL) {
                    return -1;
                }


                return(0);
            }
        }
    }


    rum_set_error("Attribute not supported for this tag");
    return -1;
}
