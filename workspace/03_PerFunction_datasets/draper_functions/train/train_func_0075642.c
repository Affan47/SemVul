is_raw_command_request( LIST * shell )
{
    return !list_empty( shell ) &&
        !strcmp( object_str( list_front( shell ) ), "%" ) &&
        list_next( list_begin( shell ) ) == list_end( shell );
}
