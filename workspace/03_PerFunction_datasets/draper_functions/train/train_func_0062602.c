var_parse_var_compile( const VAR_PARSE_VAR * parse, compiler * c )
{
    int expand_name = 0;

    if ( parse->modifiers->size > 0 )
    {
        int i;
        for ( i = 0; i < parse->modifiers->size; ++i )
        {
            var_parse_group_compile( dynamic_array_at( VAR_PARSE_GROUP *, parse->modifiers, parse->modifiers->size - i - 1 ), c );
        }
    }


    if ( parse->subscript )
    {
        var_parse_group_compile( parse->subscript, c );
    }


    if ( parse->name->elems->size == 0 )
    {
        compile_emit( c, INSTR_PUSH_VAR, compile_emit_constant( c, constant_empty ) );
    }

    else if ( parse->name->elems->size == 1 &&
        dynamic_array_at( VAR_PARSE *, parse->name->elems, 0 )->type == VAR_PARSE_TYPE_STRING )
    {
        OBJECT * name = ( (VAR_PARSE_STRING *)dynamic_array_at( VAR_PARSE *, parse->name->elems, 0 ) )->s;
        int idx = get_argument_index( object_str( name ) );
        if ( idx != -1 )
        {
            compile_emit( c, INSTR_PUSH_ARG, idx );
        }
        else
        {
            compile_emit( c, INSTR_PUSH_VAR, compile_emit_constant( c, name ) );
        }
    }

    else
    {
        var_parse_group_compile( parse->name, c );
        expand_name = 1;
    }


    if ( !parse->modifiers->size && !parse->subscript && !expand_name )
    {

    }
    else if ( !parse->modifiers->size && !parse->subscript && expand_name )
    {
        compile_emit( c, INSTR_PUSH_GROUP, 0 );
    }
    else if ( !parse->modifiers->size && parse->subscript && !expand_name )
    {
        compile_emit( c, INSTR_APPLY_INDEX, 0 );
    }
    else if ( !parse->modifiers->size && parse->subscript && expand_name )
    {
        compile_emit( c, INSTR_APPLY_INDEX_GROUP, 0 );
    }
    if ( parse->modifiers->size && !parse->subscript && !expand_name )
    {
        compile_emit( c, INSTR_APPLY_MODIFIERS, parse->modifiers->size );
    }
    else if ( parse->modifiers->size && !parse->subscript && expand_name )
    {
        compile_emit( c, INSTR_APPLY_MODIFIERS_GROUP, parse->modifiers->size );
    }
    else if ( parse->modifiers->size && parse->subscript && !expand_name )
    {
        compile_emit( c, INSTR_APPLY_INDEX_MODIFIERS, parse->modifiers->size );
    }
    else if ( parse->modifiers->size && parse->subscript && expand_name )
    {
        compile_emit( c, INSTR_APPLY_INDEX_MODIFIERS_GROUP, parse->modifiers->size );
    }
}
