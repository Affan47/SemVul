hx509_name_copy(hx509_context context, const hx509_name from, hx509_name *to)
{
    int ret;

    *to = calloc(1, sizeof(**to));
    if (*to == NULL)
	return ENOMEM;
    ret = copy_Name(&from->der_name, &(*to)->der_name);
    if (ret) {
	free(*to);
	*to = NULL;
	return ENOMEM;
    }
    return 0;
}
