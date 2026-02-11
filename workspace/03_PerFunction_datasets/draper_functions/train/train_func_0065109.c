pdfObjectReference() const
{
    if (pdfAnnot == 0)
    {
        const Ref invalid_ref = { -1, -1 };
        return invalid_ref;
    }

    return pdfAnnot->getRef();
}
