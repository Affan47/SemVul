gregorio_add_cs_to_note (gregorio_note ** current_note, char *str)
{
  if (*current_note)
    {
      (*current_note)->choral_sign = str;
    }
}
