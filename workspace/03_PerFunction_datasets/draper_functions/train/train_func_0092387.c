gabc_det_notes_from_string (char *str, char *newmacros[10])
{
  int i;
  YY_BUFFER_STATE buf;

  for (i=0;i<10;i++)
    {
      notesmacros[i] = newmacros[i];
    }
  tempstr = malloc(71*sizeof(char));
  nbof_isolated_episemus = 0;
  current_note=NULL;
  buf=gabc_notes_determination__scan_string(str);
  gabc_notes_determination_lex();
  gabc_notes_determination__flush_buffer(buf);
  gabc_notes_determination__delete_buffer(buf);
  gregorio_go_to_first_note (&current_note);
  free(tempstr);
  return current_note;
}
