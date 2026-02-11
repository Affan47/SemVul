add_user_symbol(char *raw_symb)
{
    char *symb_nam;
    char *symb_valu;

    symb_nam = strdup(raw_symb);
    symb_valu = strchr(symb_nam,'=');
    if ( symb_valu != NULL )
    {
	*symb_valu = 0;
	symb_valu++;
    }
    add_str_sub_entry(symb_nam, symb_valu, &user_symbol_list );
    user_symbol_count++;
}
