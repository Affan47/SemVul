udisks_safe_append_to_object_path (GString      *str,
                                   const gchar  *s)
{
  guint n;
  for (n = 0; s[n] != '\0'; n++)
    {
      gint c = s[n];


      if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_')
        {
          g_string_append_c (str, c);
        }
      else
        {

          g_string_append_printf (str, "_%02x", c);
        }
    }
}
