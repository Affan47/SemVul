gsc_is_string_usable (const sc_char *string)
{

  if (string)
    {
      sc_int index_;

      for (index_ = 0; string[index_] != '\0'; index_++)
        {
          if (!strchr (GSC_WHITESPACE, string[index_]))
            return TRUE;
        }
    }


  return FALSE;
}
