hwp_document_load (EvDocument *document,
                   const char *uri,
                   GError    **error)
{
    HWPDocument *hwp_document = HWP_DOCUMENT (document);
    hwp_document->document    = ghwp_document_new_from_uri (uri, error);

    if (!hwp_document->document) {
        return FALSE;
    }

    return TRUE;
}
