vlistUnpack(char * buf, int size, int *position, int nspTarget, void *context)
{
  int newvlist;
  int varID, tempbuf[vlist_nints];
  serializeUnpack(buf, size, position, tempbuf, vlist_nints, DATATYPE_INT, context);
  newvlist = vlistCreate();

  vlistDefTaxis ( newvlist, namespaceAdaptKey ( tempbuf[3], nspTarget ));
  vlistDefTable(newvlist, tempbuf[4]);
  vlistDefInstitut ( newvlist, namespaceAdaptKey ( tempbuf[5], nspTarget ));
  vlistDefModel ( newvlist, namespaceAdaptKey ( tempbuf[6], nspTarget ));
  vlistAttsUnpack(newvlist, CDI_GLOBAL, buf, size, position, context);
  for ( varID = 0; varID < tempbuf[1]; varID++ )
    vlistVarUnpack(newvlist, buf, size, position, nspTarget, context);
}
