write_func_param_struct( FILE *file, const type_t *iface, const type_t *func,
                              const char *var_decl, int add_retval )
{
    type_t *rettype = type_function_get_rettype( func );
    const var_list_t *args = type_get_function_args( func );
    const var_t *arg;
    int needs_packing;
    unsigned int align = 0;

    if (args)
        LIST_FOR_EACH_ENTRY( arg, args, const var_t, entry )
            if (!is_array( arg->type )) type_memsize_and_alignment( arg->type, &align );

    needs_packing = (align > pointer_size);

    if (needs_packing) print_file( file, 0, "#include <pshpack%u.h>\n", pointer_size );
    print_file(file, 1, "struct _PARAM_STRUCT\n" );
    print_file(file, 1, "{\n" );
    if (is_object( iface )) print_file(file, 2, "%s *This;\n", iface->name );

    if (args) LIST_FOR_EACH_ENTRY( arg, args, const var_t, entry )
    {
        print_file(file, 2, "%s", "");
        write_type_left( file, (type_t *)arg->type, TRUE );
        if (needs_space_after( arg->type )) fputc( ' ', file );
        if (is_array( arg->type ) && !type_array_is_decl_as_ptr( arg->type )) fputc( '*', file );


        align = 0;
        if (is_array( arg->type ) || is_ptr( arg->type )) align = pointer_size;
        else type_memsize_and_alignment( arg->type, &align );

        if (align >= pointer_size)
            fprintf( file, "%s;\n", arg->name );
        else
            fprintf( file, "%s DECLSPEC_ALIGN(%u);\n", arg->name, pointer_size );
    }
    if (add_retval && !is_void( rettype ))
    {
        print_file(file, 2, "%s", "");
        write_type_decl( file, rettype, "_RetVal" );
        if (is_array( rettype ) || is_ptr( rettype ) || type_memsize( rettype ) == pointer_size)
            fprintf( file, ";\n" );
        else
            fprintf( file, " DECLSPEC_ALIGN(%u);\n", pointer_size );
    }
    print_file(file, 1, "} %s;\n", var_decl );
    if (needs_packing) print_file( file, 0, "#include <poppack.h>\n" );
    print_file( file, 0, "\n" );
}
