i_free_shared_class(type_cclass_key* key, Node* node, void* arg ARG_UNUSED)
{
  if (IS_NOT_NULL(node)) {
    CClassNode* cc = NCCLASS(node);
    if (IS_NOT_NULL(cc->mbuf)) xfree(cc->mbuf);
    xfree(node);
  }

  if (IS_NOT_NULL(key)) xfree(key);
  return ST_DELETE;
}
