string_list_copy_constructor(string_list_ty *to, const string_list_ty *from)
{
    size_t          j;

    string_list_constructor(to);
    for (j = 0; j < from->nstrings; j++)
        string_list_append(to, str_copy(from->string[j]));
}
