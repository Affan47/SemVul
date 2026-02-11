hwp_document_get_info (EvDocument *document)
{
    EvDocumentInfo *info;
    GHWPDocument   *ghwp_doc;

    info = g_new0 (EvDocumentInfo, 1);
    info->fields_mask = EV_DOCUMENT_INFO_TITLE         |
                        EV_DOCUMENT_INFO_FORMAT        |
                        EV_DOCUMENT_INFO_SUBJECT       |
                        EV_DOCUMENT_INFO_KEYWORDS      |
                        EV_DOCUMENT_INFO_CREATOR       |
                        EV_DOCUMENT_INFO_CREATION_DATE |
                        EV_DOCUMENT_INFO_MOD_DATE;

    ghwp_doc = HWP_DOCUMENT (document)->document;

    info->title    = ghwp_document_get_title    (ghwp_doc);
    info->format   = ghwp_document_get_format   (ghwp_doc);
    info->subject  = ghwp_document_get_subject  (ghwp_doc);
    info->keywords = ghwp_document_get_keywords (ghwp_doc);
    info->creator  = ghwp_document_get_creator  (ghwp_doc);
    info->creation_date = ghwp_document_get_creation_date     (ghwp_doc);
    info->modified_date = ghwp_document_get_modification_date (ghwp_doc);

    return info;
}
