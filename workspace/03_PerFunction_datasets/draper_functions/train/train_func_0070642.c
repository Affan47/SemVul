tieToNativeAnnot(Annot *ann, ::Page *page, Poppler::DocumentData * doc)
{
    if (pdfAnnot)
    {
        error(errIO, -1, "Annotation is already tied");
        return;
    }

    pdfAnnot = ann;
    pdfPage = page;
    parentDoc = doc;

    pdfAnnot->incRefCnt();
}
