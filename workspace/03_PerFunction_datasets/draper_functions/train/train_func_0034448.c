_new_FreeListNode(FreeList *fl)
{
  void *node;


  if(!fl)
    return NULL;


  if(!fl->free_list) {
    FreeListBlock *block = _new_FreeListBlock(fl);
    if(!block)
      return NULL;


    block->next = fl->block;
    fl->block = block;


    fl->free_list = fl->block->nodes;
  };


  node = fl->free_list;
  fl->free_list = *(void **)node;


  fl->nbusy++;


  return node;
}
