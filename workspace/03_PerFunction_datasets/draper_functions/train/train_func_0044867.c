name_map(char *symb)
{
    register int i;
    register struct hash_type *p;

    i = hash(symb);
    for (p = hash_table[i]; p != NULL; p = p -> link)
    {
        if (EQUAL_STRING(symb, p))
        {
            if (p -> name_index != OMEGA)
                return(p -> name_index);
            else
            {
                num_names++;
                p -> name_index = num_names;
                return(num_names);
            }
        }
    }

    p = (struct hash_type *) talloc(sizeof(struct hash_type));
    if (p == (struct hash_type *) NULL)
        nospace(__FILE__, __LINE__);
    p -> number = 0;
    insert_string(p, symb);
    p -> link = hash_table[i];
    hash_table[i] = p;

    num_names++;
    p -> name_index = num_names;

    return num_names;
}
