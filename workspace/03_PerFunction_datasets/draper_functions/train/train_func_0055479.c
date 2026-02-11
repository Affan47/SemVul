exit_process(void)
{
    if (string_offset > 0)
    {
        string_table = (char *)
            (string_table == (char *) NULL
             ? malloc((string_offset) * sizeof(char))
             : realloc(string_table, (string_offset) * sizeof(char)));

        if (string_table == (char *) NULL)
            nospace(__FILE__, __LINE__);
    }
    ffree(terminal);
    ffree(hash_table);
    ffree(input_buffer);
    ffree(rulehdr);

    return;
}
