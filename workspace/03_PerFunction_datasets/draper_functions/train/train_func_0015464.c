mock_get_display_name(const QofInstance* inst)
{
    gchar *display_name;

    g_assert( inst );
    g_assert( QOF_INSTANCE_GET_CLASS( inst )->get_display_name == mock_get_display_name );
    is_called = TRUE;
    display_name = g_strdup_printf("Mock display name %p", inst );
    return display_name;
}
