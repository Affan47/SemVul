mock_simple_refers_to_object( const QofInstance* inst, const QofInstance* ref )
{
    g_assert( inst );
    g_assert( ref );
    if ( inst->e_type == ref->e_type )
    {
        get_referring_object_list_struct.refers_to_object_call_count++;
        return TRUE;
    }
    return FALSE;
}
