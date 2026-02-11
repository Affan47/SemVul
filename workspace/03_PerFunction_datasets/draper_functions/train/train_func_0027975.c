setup( Fixture *fixture, gconstpointer pData )
{
    fixture->session = qof_session_new();
    init_static_qofsession_pointers ();
    g_assert (p_qof_session_clear_error && p_qof_session_destroy_backend && p_qof_session_load_backend);
}
