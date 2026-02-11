xml_goto_root(struct xml_handle *handle_p)
{
  if(handle_p==NULL)  return;

  while(handle_p->child_handle_p!=NULL)
  {
    handle_p = handle_p->child_handle_p;
  }

  while(handle_p->level!=0)
  {
    if(handle_p->elementname != NULL)  free(handle_p->elementname);
    if(handle_p->attributes != NULL)  free(handle_p->attributes);
    if(handle_p->tag_search_result != NULL)  free(handle_p->tag_search_result);

    handle_p = handle_p->parent_handle_p;

    free(handle_p->child_handle_p);
  }

  handle_p->child_handle_p = NULL;
}
