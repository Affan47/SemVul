pdf_find_resource_by_gs_id(gx_device_pdf * pdev, pdf_resource_type_t rtype,
                           gs_id rid)
{
    pdf_resource_t **pchain = PDF_RESOURCE_CHAIN(pdev, rtype, rid);
    pdf_resource_t **pprev = pchain;
    pdf_resource_t *pres;

    for (; (pres = *pprev) != 0; pprev = &pres->next)
        if (pres->rid == rid) {
            if (pprev != pchain) {
                *pprev = pres->next;
                pres->next = *pchain;
                *pchain = pres;
            }
            return pres;
        }
    return 0;
}
