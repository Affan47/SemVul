write_code_const_c(ARGUMENTS *args,
                       GWEN_XMLNODE *node,
                       GWEN_SYNCIO *sio){
  const char *prefix;
  const char *styp;
  const char *constName;
  int rv;

  prefix=get_struct_property(node, "prefix", 0);
  if (!prefix) {
    DBG_ERROR(0, "No prefix in struct");
    return -1;
  }
  styp=get_struct_property(node, "id", 0);
  if (!styp) {
    DBG_ERROR(0, "No id in struct");
    return -1;
  }
  constName=get_struct_property(node, "constructor-name", 0);

  GWEN_SyncIo_WriteString(sio, styp);
  GWEN_SyncIo_WriteString(sio, " *");
  GWEN_SyncIo_WriteString(sio, prefix);
  if (constName && *constName)
    GWEN_SyncIo_WriteString(sio, constName);
  else
    GWEN_SyncIo_WriteString(sio, "_new");
  GWEN_SyncIo_WriteLine(sio, "(void) {");

  GWEN_SyncIo_WriteString(sio, "  ");
  GWEN_SyncIo_WriteString(sio, styp);
  GWEN_SyncIo_WriteLine(sio, " *st;");
  GWEN_SyncIo_WriteLine(sio, "");

  GWEN_SyncIo_WriteString(sio, "  GWEN_NEW_OBJECT(");
  GWEN_SyncIo_WriteString(sio, styp);
  GWEN_SyncIo_WriteLine(sio, ", st)");
  GWEN_SyncIo_WriteLine(sio, "  st->_usage=1;");


  if (get_struct_property(node, "inherit", 0)) {
    GWEN_SyncIo_WriteString(sio, "  GWEN_INHERIT_INIT(");
    GWEN_SyncIo_WriteString(sio, styp);
    GWEN_SyncIo_WriteLine(sio, ", st)");
  }


  if (get_struct_property(node, "list", 0)) {
    GWEN_SyncIo_WriteString(sio, "  GWEN_LIST_INIT(");
    GWEN_SyncIo_WriteString(sio, styp);
    GWEN_SyncIo_WriteLine(sio, ", st)");
  }

  rv=write_code_constrec_c(args, node, sio);
  if (rv)
    return rv;

  GWEN_SyncIo_WriteLine(sio, "  return st;");
  GWEN_SyncIo_WriteLine(sio, "}");

  return 0;
}
