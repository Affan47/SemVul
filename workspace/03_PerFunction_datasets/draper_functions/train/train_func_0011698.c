write_code_dest_c(ARGUMENTS *args,
                      GWEN_XMLNODE *node,
                      GWEN_SYNCIO *sio){
  const char *prefix;
  const char *styp;
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

  GWEN_SyncIo_WriteString(sio, "void ");
  GWEN_SyncIo_WriteString(sio, prefix);
  GWEN_SyncIo_WriteString(sio, "_free(");
  GWEN_SyncIo_WriteString(sio, styp);
  GWEN_SyncIo_WriteLine(sio, " *st) {");

  GWEN_SyncIo_WriteLine(sio, "  if (st) {");

  GWEN_SyncIo_WriteLine(sio, "    assert(st->_usage);");
  GWEN_SyncIo_WriteLine(sio, "    if (--(st->_usage)==0) {");


  if (get_struct_property(node, "inherit", 0)) {
    GWEN_SyncIo_WriteString(sio, "  GWEN_INHERIT_FINI(");
    GWEN_SyncIo_WriteString(sio, styp);
    GWEN_SyncIo_WriteLine(sio, ", st)");
  }

  rv=write_code_freeElems_c(args, node, sio);
  if (rv) {
    DBG_ERROR(0, "Error in freeElems");
    return rv;
  }


  if (get_struct_property(node, "list", 0)) {
    GWEN_SyncIo_WriteString(sio, "  GWEN_LIST_FINI(");
    GWEN_SyncIo_WriteString(sio, styp);
    GWEN_SyncIo_WriteLine(sio, ", st)");
  }

  GWEN_SyncIo_WriteLine(sio, "  GWEN_FREE_OBJECT(st);");
  GWEN_SyncIo_WriteLine(sio, "    }");
  GWEN_SyncIo_WriteLine(sio, "  }");
  GWEN_SyncIo_WriteLine(sio, "");
  GWEN_SyncIo_WriteLine(sio, "}");

  return 0;
}
