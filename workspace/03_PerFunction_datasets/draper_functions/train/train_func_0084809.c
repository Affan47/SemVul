init_style()
{
  if (sort_flag == 0 || sortcol != 0)
    error->all(FLERR,"Dump xtc requires sorting by atom ID");


  if (flush_flag) error->all(FLERR,"Cannot set dump_modify flush for dump xtc");


  int idump;
  for (idump = 0; idump < output->ndump; idump++)
    if (strcmp(id,output->dump[idump]->id) == 0) break;
  if (output->every_dump[idump] == 0)
    error->all(FLERR,"Cannot use variable every setting for dump xtc");

  if (nevery_save == 0) nevery_save = output->every_dump[idump];
  else if (nevery_save != output->every_dump[idump])
    error->all(FLERR,"Cannot change dump_modify every for dump xtc");
}
