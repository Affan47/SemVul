close()
{
    if( !file ) return FALSE;

    t_CKBOOL value = fclose( file ) == 0;


    std::map<MidiRW *, MidiRW *>::iterator iter;
    iter = g_rw.find( this );
    g_rw.erase( iter );

    file = NULL;

    return value;
}
