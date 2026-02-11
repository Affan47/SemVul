xsh_dump_arclist( xsh_arclist* list)
{
  int i = 0;

  XSH_ASSURE_NOT_NULL(list);

  xsh_msg( "ARCLINE_LIST Dump %d lines",list->size);

  for(i=0; i< list->size; i++) {
    const char* name = list->list[i]->name;
    const char* comment = list->list[i]->comment;
    if (name == NULL) name ="";
    if (comment == NULL) comment ="";
    xsh_msg("  Wavelength %f name %s flux %d comment %s",
      list->list[i]->wavelength, name,
      list->list[i]->flux, comment);
  }
  xsh_msg( "END ARCLINE_LIST");

  cleanup:
    return;
}
