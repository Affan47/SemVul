var_parse_compile( const VAR_PARSE * parse, compiler * c )
{
    if( parse->type == VAR_PARSE_TYPE_VAR )
    {
        var_parse_var_compile( (const VAR_PARSE_VAR *)parse, c );
    }
    else if( parse->type == VAR_PARSE_TYPE_STRING )
    {
        var_parse_string_compile( (const VAR_PARSE_STRING *)parse, c );
    }
    else if( parse->type == VAR_PARSE_TYPE_FILE )
    {
        var_parse_file_compile( (const VAR_PARSE_FILE *)parse, c );
    }
    else
    {
        assert( !"Unknown var parse type." );
    }
}
