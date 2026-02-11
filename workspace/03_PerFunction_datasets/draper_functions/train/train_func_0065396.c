pre_MembPtrExpr (CT_MembPtrExpr *node) {
  CObjectInfo *obj = node->Object ();


  if (!register_access (obj, node))
    return;


  visit (node->Son (0));

  CTree *name = node->Son (2);
  const char *id = name->NodeName ();
  if (id == CT_QualName::NodeId () ||
      id == CT_RootQualName::NodeId ()) {
    CT_QualName *qual_name = (CT_QualName*)name;
    for (int i = 0; i < qual_name->Entries () - 1; i++)
      visit (qual_name->Entry (i));
  }


  prune ();
}
