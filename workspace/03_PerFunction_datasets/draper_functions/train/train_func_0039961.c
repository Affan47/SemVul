builtin_delete_module( FRAME * frame, int flags )
{
    LIST     * arg0 = lol_get( frame->args, 0 );
    LIST     * result = L0;
    module_t * source_module = bindmodule( !list_empty(arg0) ? list_front(arg0) : 0 );
    delete_module( source_module );
    return result;
}
