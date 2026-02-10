compare_int_fields(xmlNode * left, xmlNode * right, const char *field)
{
    const char *elem_l = crm_element_value(left, field);
    const char *elem_r = crm_element_value(right, field);

    int int_elem_l = crm_int_helper(elem_l, NULL);
    int int_elem_r = crm_int_helper(elem_r, NULL);

    if (int_elem_l < int_elem_r) {
        return -1;

    } else if (int_elem_l > int_elem_r) {
        return 1;
    }

    return 0;
}
