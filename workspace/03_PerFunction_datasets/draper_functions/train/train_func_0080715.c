cipher_list( void )
{
    const cipher_definition_t *def;
    int *type;

    if( ! supported_init )
    {
        def = cipher_definitions;
        type = supported_ciphers;

        while( def->type != 0 )
            *type++ = (*def++).type;

        *type = 0;

        supported_init = 1;
    }

    return supported_ciphers;
}
