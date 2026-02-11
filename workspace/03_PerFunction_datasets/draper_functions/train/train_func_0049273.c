get_afe_values (SANE_String_Const cp, GT68xx_AFE_Parameters * afe)
{
  SANE_Char *word, *end;
  int i;

  for (i = 0; i < 6; i++)
    {
      cp = sanei_config_get_string (cp, &word);
      if (word && *word)
        {
          long int long_value;
          errno = 0;
          long_value = strtol (word, &end, 0);

          if (end == word)
            {
              DBG (5, "get_afe_values: can't parse %d. parameter `%s'\n",
                   i + 1, word);
              free (word);
              word = 0;
              return SANE_STATUS_INVAL;
            }
          else if (errno)
            {
              DBG (5, "get_afe_values: can't parse %d. parameter `%s' "
                   "(%s)\n", i + 1, word, strerror (errno));
              free (word);
              word = 0;
              return SANE_STATUS_INVAL;
            }
          else if (long_value < 0)
            {
              DBG (5, "get_afe_values: %d. parameter < 0 (%d)\n", i + 1,
                   (int) long_value);
              free (word);
              word = 0;
              return SANE_STATUS_INVAL;
            }
          else if (long_value > 0x3f)
            {
              DBG (5, "get_afe_values: %d. parameter > 0x3f (%d)\n", i + 1,
                   (int) long_value);
              free (word);
              word = 0;
              return SANE_STATUS_INVAL;
            }
          else
            {
              DBG (5, "get_afe_values: %d. parameter set to 0x%02x\n", i + 1,
                   (int) long_value);
              switch (i)
                {
                case 0:
                  afe->r_offset = (SANE_Byte) long_value;
                  break;
                case 1:
                  afe->r_pga = (SANE_Byte) long_value;
                  break;
                case 2:
                  afe->g_offset = (SANE_Byte) long_value;
                  break;
                case 3:
                  afe->g_pga = (SANE_Byte) long_value;
                  break;
                case 4:
                  afe->b_offset = (SANE_Byte) long_value;
                  break;
                case 5:
                  afe->b_pga = (SANE_Byte) long_value;
                  break;
                }
              free (word);
              word = 0;
            }
        }
      else
        {
          DBG (5, "get_afe_values: option `afe' needs 6  parameters\n");
          return SANE_STATUS_INVAL;
        }
    }
  return SANE_STATUS_GOOD;
}
