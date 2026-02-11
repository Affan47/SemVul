document_manager_get_current_documentable (DocumentManager *docmg)
{
  gphpedit_debug(DEBUG_DOC_MANAGER);
  if (!docmg) return NULL;
  DocumentManagerDetails *docmgdet = DOCUMENT_MANAGER_GET_PRIVATE(docmg);
  return DOCUMENTABLE(docmgdet->current_document);
}
