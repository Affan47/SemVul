pam_messages_cb (Session *session, Greeter *greeter)
{
    int i;
    guint32 size;
    guint8 message[MAX_MESSAGE_LENGTH];
    const struct pam_message *messages;
    int messages_length;
    gsize offset = 0;
    int n_prompts = 0;

    messages = session_get_messages (session);
    messages_length = session_get_messages_length (session);


    l_debug (greeter, "Prompt greeter with %d message(s)", messages_length);
    size = int_length () + string_length (session_get_username (session)) + int_length ();
    for (i = 0; i < messages_length; i++)
        size += int_length () + string_length (messages[i].msg);

    write_header (message, MAX_MESSAGE_LENGTH, SERVER_MESSAGE_PROMPT_AUTHENTICATION, size, &offset);
    write_int (message, MAX_MESSAGE_LENGTH, greeter->priv->authentication_sequence_number, &offset);
    write_string (message, MAX_MESSAGE_LENGTH, session_get_username (session), &offset);
    write_int (message, MAX_MESSAGE_LENGTH, messages_length, &offset);
    for (i = 0; i < messages_length; i++)
    {
        write_int (message, MAX_MESSAGE_LENGTH, messages[i].msg_style, &offset);
        write_string (message, MAX_MESSAGE_LENGTH, messages[i].msg, &offset);

        if (messages[i].msg_style == PAM_PROMPT_ECHO_OFF || messages[i].msg_style == PAM_PROMPT_ECHO_ON)
            n_prompts++;
    }
    write_message (greeter, message, offset);


    if (n_prompts == 0)
    {
        struct pam_response *response;
        response = calloc (messages_length, sizeof (struct pam_response));
        session_respond (greeter->priv->authentication_session, response);
        free (response);
    }
}
