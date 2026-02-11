document_manager_get_document_count (DocumentManager *docmg)
{
  gphpedit_debug(DEBUG_DOC_MANAGER);
  if (!docmg) return 0;
  DocumentManagerDetails *docmgdet = DOCUMENT_MANAGER_GET_PRIVATE(docmg);
  if (!docmgdet->editors) return 0;
  return g_slist_length(docmgdet->editors);
}
