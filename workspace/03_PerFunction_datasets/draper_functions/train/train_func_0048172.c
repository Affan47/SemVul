pdf_resize_page (pdf_t *doc,
                                 int page,
                                 float width,
                                 float length,
                                 float *scale)
{
    XRef *xref = doc->getXRef();
    Ref *pageref = doc->getCatalog()->getPageRef(page);
    Object pageobj;
    float mediabox[4] = { 0.0, 0.0, width, length };
    float old_mediabox[4];

    xref->fetch(pageref->num, pageref->gen, &pageobj);
    if (!pageobj.isDict()) {
        fprintf(stderr, "Error: malformed pdf\n");
        return;
    }

    if (!dict_lookup_rect (&pageobj, "MediaBox", old_mediabox)) {
        fprintf(stderr, "Error: pdf doesn't contain a valid mediabox\n");
        return;
    }

    fit_rect(old_mediabox, mediabox, scale);

    dict_set_rect (xref, &pageobj, "MediaBox", mediabox);
    dict_set_rect (xref, &pageobj, "CropBox", mediabox);
    dict_set_rect (xref, &pageobj, "TrimBox", mediabox);
    dict_set_rect (xref, &pageobj, "ArtBox", mediabox);
    dict_set_rect (xref, &pageobj, "BleedBox", mediabox);

    xref->setModifiedObject(&pageobj, *pageref);
    pageobj.free();
}
