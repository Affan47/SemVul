gsc_handle_font_tag (const sc_char *argument)
{

  if (gsc_font_index < GSC_MAX_STYLE_NESTING)
    {
      sc_char *lower, *face, *size;
      sc_bool is_monospaced;
      sc_int index_, font_size;


      if (gsc_font_index > 0)
        {
          is_monospaced = gsc_font_stack[gsc_font_index - 1].is_monospaced;
          font_size = gsc_font_stack[gsc_font_index - 1].size;
        }
      else
        {
          is_monospaced = FALSE;
          font_size = GSC_DEFAULT_FONT_SIZE;
        }


      lower = gsc_malloc (strlen (argument) + 1);
      strcpy (lower, argument);
      for (index_ = 0; lower[index_] != '\0'; index_++)
        lower[index_] = glk_char_to_lower (lower[index_]);


      face = strstr (lower, "face=");
      if (face)
        {


          is_monospaced = strncmp (face, "face=\"courier\"", 14) == 0
                          || strncmp (face, "face=\"terminal\"", 15) == 0;
        }


      size = strstr (lower, "size=");
      if (size)
        {
          sc_uint value;


          if (strncmp (size, "size=+", 6) == 0
              && sscanf (size, "size=+%lu", &value) == 1)
            font_size += value;
          else if (strncmp (size, "size=-", 6) == 0
                   && sscanf (size, "size=-%lu", &value) == 1)
            font_size -= value;
          else if (sscanf (size, "size=%lu", &value) == 1)
            font_size = value;
        }


      free (lower);


      gsc_font_stack[gsc_font_index].is_monospaced = is_monospaced;
      gsc_font_stack[gsc_font_index++].size = font_size;
      gsc_set_glk_style ();
    }
}
