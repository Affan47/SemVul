luaconsole_dialog_init(void)
{
  fc_assert_ret(luaconsole == NULL);


  luaconsole = fc_calloc(1, sizeof(*luaconsole));
  luaconsole->message_buffer = gtk_text_buffer_new(NULL);
  luaconsole->shell = NULL;

  luaconsole->history_list = genlist_new();
  luaconsole->history_pos = -1;

  luaconsole_welcome_message();
}
