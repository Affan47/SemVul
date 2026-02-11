pdf_add_procsets(cos_dict_t *pcd, pdf_procset_t procsets)
{
    char str[5 + 7 + 7 + 7 + 5 + 2];
    cos_value_t v;

    strcpy(str, "[/PDF");
    if (procsets & ImageB)
        strcat(str, "/ImageB");
    if (procsets & ImageC)
        strcat(str, "/ImageC");
    if (procsets & ImageI)
        strcat(str, "/ImageI");
    if (procsets & Text)
        strcat(str, "/Text");
    strcat(str, "]");
    cos_string_value(&v, (byte *)str, strlen(str));
    return cos_dict_put_c_key(pcd, "/ProcSet", &v);
}
