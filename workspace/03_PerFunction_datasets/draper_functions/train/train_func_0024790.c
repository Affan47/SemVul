HPDF_URILinkAnnot_New  (HPDF_MMgr          mmgr,
                        HPDF_Xref          xref,
                        HPDF_Rect          rect,
                        const char   *uri)
{
    HPDF_Annotation annot;
    HPDF_Dict action;
    HPDF_STATUS ret;

    HPDF_PTRACE((" HPDF_URILinkAnnot_New\n"));

    annot = HPDF_Annotation_New (mmgr, xref, HPDF_ANNOT_LINK, rect);
    if (!annot)
        return NULL;


    action = HPDF_Dict_New (mmgr);
    if (!action)
        return NULL;

    ret = HPDF_Dict_Add (annot, "A", action);
    if (ret != HPDF_OK)
        return NULL;

    ret += HPDF_Dict_AddName (action, "Type", "Action");
    ret += HPDF_Dict_AddName (action, "S", "URI");
    ret += HPDF_Dict_Add (action, "URI", HPDF_String_New (mmgr, uri, NULL));

    if (ret != HPDF_OK)
        return NULL;

    return annot;
}
