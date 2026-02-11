add_to_list(hx509_octet_string_list *list, const heim_octet_string *entry)
{
    void *p;
    int ret;

    p = realloc(list->val, (list->len + 1) * sizeof(list->val[0]));
    if (p == NULL)
	return ENOMEM;
    list->val = p;
    ret = der_copy_octet_string(entry, &list->val[list->len]);
    if (ret)
	return ret;
    list->len++;
    return 0;
}
