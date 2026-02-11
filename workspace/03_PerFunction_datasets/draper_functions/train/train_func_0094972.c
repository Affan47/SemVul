question_conditional_yes_no_get_no_struct ( struct conditional_message *msg,
                        gchar *name )
{
    gint i;

    for  ( i = 0; msg[i].name; i++ )
    {
        if ( strcmp ( msg[i].name, name ) == 0 )
            return i;
    }
    return -1;
}
