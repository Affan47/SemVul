get_dimension_list(Lsymtab *symt)
#else
get_dimension_list(symt)
     Lsymtab *symt;
#endif
{
    int n, dims;


    new_fragment();

    append_char_to_fragment('(');

    dims = array_dims(symt->info.array_dim);
    for (n = 0; n < dims; ++n)
    {
	if (n > 0)
	    append_char_to_fragment(',');
	append_expr_text_to_fragment(symt->src.textvec[n]);
    }

    append_char_to_fragment(')');
    append_char_to_fragment('\0');

    return (&stmt_fragment[0]);
}
