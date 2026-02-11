string_to_list (krb5_context context, const char *s, krb5_realm **list)
{

    *list = malloc (2 * sizeof(**list));
    if (*list == NULL)
	return krb5_enomem(context);
    (*list)[0] = strdup (s);
    if ((*list)[0] == NULL) {
	free (*list);
	return krb5_enomem(context);
    }
    (*list)[1] = NULL;
    return 0;
}
