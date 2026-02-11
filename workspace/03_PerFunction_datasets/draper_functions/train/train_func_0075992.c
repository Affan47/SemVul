print_declaration_class(Lsymtab **sym_list, int n, const char *header)
#else
print_declaration_class(sym_list, n, header)
     Lsymtab *sym_list[];
     int n;
     char *header;
#endif
{
    unsigned t;
    static int types_table[] =
    {
	type_STRING,
	type_COMPLEX,
	type_DCOMPLEX,
	type_DP,
	type_INTEGER,
	type_LOGICAL,
	type_REAL,
    };

    if (n > 0)
    {
	for (t = 0; t < sizeof(types_table)/sizeof(types_table[0]); ++t)
	    print_selected_declarations(sym_list, n, types_table[t],
					(char*)NULL, &header);
    }
}
