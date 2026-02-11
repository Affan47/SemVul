error_table_print(gpointer key, gpointer value, gpointer data)
{
gchar *msg, *text = key;
gint *count = value;


if (*count > MAX_ERROR_COUNT)
  msg = g_strdup_printf("[count >%d] %s", MAX_ERROR_COUNT, text);
else
  msg = g_strdup_printf("[count %d] %s", *count, text);

gui_text_show(ERROR,msg);

g_free(msg);
}
