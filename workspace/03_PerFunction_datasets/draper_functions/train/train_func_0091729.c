parser_get_next_line()
{
    char *line = cbuffer_pos;
    char *newpos;
    if ( cbuffer_pos[0] == 0 )
        return 0;
    if ( ( newpos = strchr( cbuffer_pos, 10 ) ) == 0 )
        cbuffer_pos += strlen( cbuffer_pos );
    else {
        cbuffer_pos = newpos + 1;
        newpos[0] = 0;
    }
    return line;
}
