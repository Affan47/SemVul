eXdbmChangeEntryComment(DB_ID dbid, DB_LIST list, char *entryname, char *comment)
{
  TDbmListEntry *search;
  int ret;


  ret = DbmIsInit();
  if( ret == -1) return(-1);


  if(CheckDbIdent(dbid) == -1) {
    RaiseError(DBM_WRONG_ID);
    return(-1);
  }


  if(comment==NULL) {
    RaiseError(DBM_BAD_PARAMETER);
    return(-1);
  }


  if(list==NULL)

    search = SearchListEntry(DbmDbList->dblist[dbid].root, entryname);

  else

    search = SearchListEntry(list, entryname);

  if (search==NULL) return(DBM_ENTRY_NOT_FOUND);


  if(search->comment!=NULL) free(search->comment);

  search->comment = (char *) malloc( sizeof(char) * (strlen(comment)+1));
  if(search->comment == NULL) {
    RaiseError(DBM_ALLOC);
    return(-1);
  }

  strcpy(search->comment, comment);

  return(1);

}
