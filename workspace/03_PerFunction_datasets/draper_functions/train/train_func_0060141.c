ekiga_dialpad_get_button_code (G_GNUC_UNUSED EkigaDialpad *dialpad,
                               char          number)
{
  unsigned i;
  for (i = 0; i < G_N_ELEMENTS (keys_info); i++)
    if (keys_info[i].number[0] == number)
      return keys_info[i].code;
  return 0;
}
