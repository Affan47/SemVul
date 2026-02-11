stringset_two(string_list_ty *result)
{
    stringset_three(result);
    while (stringset_token == STRINGSET_STAR)
    {
        string_list_ty  lhs;
        string_list_ty  rhs;
        size_t          j;
        string_ty       *s;

        stringset_lex();
        string_list_constructor(&rhs);
        stringset_three(&rhs);
        lhs = *result;
        string_list_constructor(result);
        for (j = 0; j < rhs.nstrings; ++j)
        {
            s = rhs.string[j];
            if (string_list_member(&lhs, s))
                string_list_append_unique(result, s);
        }
        string_list_destructor(&lhs);
        string_list_destructor(&rhs);
    }
}
