gifti_intent_from_string( const char * name )
{
    int tablen = sizeof(gifti_intent_list)/sizeof(gifti_intent_ele);
    int c;

    if( !name ) return 0;

    for( c = tablen-1; c > 0; c-- )
        if( !strcmp(name, gifti_intent_list[c].name) )
            break;

    return gifti_intent_list[c].code;
}
