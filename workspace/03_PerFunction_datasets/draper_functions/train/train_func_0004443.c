http_header_add(List *headers, char *name, char *contents)
{
    gwlib_assert_init();
    gw_assert(headers != NULL);
    gw_assert(name != NULL);
    gw_assert(contents != NULL);

    gwlist_append(headers, octstr_format("%s: %s", name, contents));
}
