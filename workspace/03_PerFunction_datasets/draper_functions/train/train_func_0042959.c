command_select_shared_ant(ParsingByteStream &)
{
  GP<DjVmDir::File> frec = g().doc->get_djvm_dir()->get_shared_anno_file();
  if (! frec)
    verror("select-shared-ant: no shared annotation file");
  select_clear();
  select_add(frec);
  vprint("select-shared-ant: selecting shared annotation");
}
