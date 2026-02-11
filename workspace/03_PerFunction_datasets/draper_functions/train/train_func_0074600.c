del_ExpandFile(ExpandFile *ef)
{
  if(ef) {
    DirNode *dnode;


    ef->sg = _del_StringGroup(ef->sg);


    for(dnode=ef->cache.head; dnode; dnode=dnode->next)
      dnode->dr = _del_DirReader(dnode->dr);


    ef->cache.mem = _del_FreeList(ef->cache.mem, 1);
    ef->cache.head = ef->cache.tail = ef->cache.next = NULL;


    ef->path = _del_PathName(ef->path);


    ef->home = _del_HomeDir(ef->home);


    if(ef->result.files) {
      free(ef->result.files);
      ef->result.files = NULL;
    };


    ef->err = _del_ErrMsg(ef->err);


    free(ef);
  };
  return NULL;
}
