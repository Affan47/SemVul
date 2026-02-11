try_tag_implicit( SyckNode *n, int taguri )
{
    const char *tid = "";
    switch ( n->kind )
    {
        case syck_str_kind:
            tid = syck_match_implicit( n->data.str->ptr, n->data.str->len );
        break;

        case syck_seq_kind:
            tid = "seq";
        break;

        case syck_map_kind:
            tid = "map";
        break;
    }
    if ( n->type_id != NULL ) S_FREE( n->type_id );
    if ( taguri == 1 )
    {
        n->type_id = syck_taguri( YAML_DOMAIN, tid, (int)strlen( tid ) );
    } else {
        n->type_id = syck_strndup( tid, (int)strlen( tid ) );
    }
}
