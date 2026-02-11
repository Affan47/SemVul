get_send_range_nolock(mca_pml_bfo_send_request_t* sendreq)
{
    opal_list_item_t *item;

    item = opal_list_get_first(&sendreq->req_send_ranges);

    if(opal_list_get_end(&sendreq->req_send_ranges) == item)
        return NULL;

    return (mca_pml_bfo_send_range_t*)item;
}
