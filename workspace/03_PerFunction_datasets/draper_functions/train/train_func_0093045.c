pdf_record_usage(gx_device_pdf *const pdev, long resource_id, int page_num)
{
    int i;
    void *Temp;
    pdf_linearisation_record_t *resize;

    if (!pdev->Linearise)
        return 0;

    if (resource_id < 0)
        return 0;

    if (resource_id >= pdev->ResourceUsageSize) {
        if (pdev->ResourceUsageSize == 0) {
            pdev->ResourceUsageSize = resource_id + 1;
            pdev->ResourceUsage = gs_alloc_struct_array(pdev->pdf_memory, resource_id + 1, pdf_linearisation_record_t,
                              &st_pdf_linearisation_record_element, "start resource usage array");
            memset((char *)pdev->ResourceUsage, 0x00, (resource_id + 1) * sizeof(pdf_linearisation_record_t));
        } else {
            resize = gs_resize_object(pdev->pdf_memory, pdev->ResourceUsage, resource_id + 1, "resize resource usage array");
            memset(&resize[pdev->ResourceUsageSize], 0x00, sizeof(pdf_linearisation_record_t) * (resource_id - pdev->ResourceUsageSize + 1));
            pdev->ResourceUsageSize = resource_id + 1;
            pdev->ResourceUsage = resize;
        }
    }
    if (page_num > 0) {
        if (pdev->ResourceUsage[resource_id].PageUsage == 0)
            pdev->ResourceUsage[resource_id].PageUsage = page_num;
        else {
            if (pdev->ResourceUsage[resource_id].PageUsage > 1)
                pdev->ResourceUsage[resource_id].PageUsage = resource_usage_page_shared;
            else {

            }
        }
    } else {
        if (pdev->ResourceUsage[resource_id].PageUsage != 0)

            ;
        pdev->ResourceUsage[resource_id].PageUsage = page_num;
    }


    if (pdev->ResourceUsage[resource_id].NumPagesUsing != 0) {
        for (i=0;i < pdev->ResourceUsage[resource_id].NumPagesUsing; i++) {
            if (pdev->ResourceUsage[resource_id].PageList[i] == page_num)
                return 0;
        }
    }
    Temp = gs_alloc_bytes(pdev->pdf_memory, (pdev->ResourceUsage[resource_id].NumPagesUsing + 1) * sizeof (int), "Page usage records");
    memset((char *)Temp, 0x00, (pdev->ResourceUsage[resource_id].NumPagesUsing + 1) * sizeof (int));
    memcpy((char *)Temp, pdev->ResourceUsage[resource_id].PageList, pdev->ResourceUsage[resource_id].NumPagesUsing * sizeof (int));
    gs_free_object(pdev->pdf_memory, (byte *)pdev->ResourceUsage[resource_id].PageList, "Free old page usage records");
    pdev->ResourceUsage[resource_id].PageList = (int *)Temp;
    pdev->ResourceUsage[resource_id].PageList[pdev->ResourceUsage[resource_id].NumPagesUsing] = page_num;
    pdev->ResourceUsage[resource_id].NumPagesUsing++;

    return 0;
}
