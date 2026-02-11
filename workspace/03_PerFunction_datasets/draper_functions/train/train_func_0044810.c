quit_listening(void)
{
    if ( lpeobject == NULL ) {
        return;
    }
    _modified_connection.disconnect();
    _delete_connection.disconnect();
    lpeobject_repr = NULL;
    lpeobject = NULL;
}
