opvp_startpage(gx_device *dev)
{
    int ecode = 0;
    opvp_result_t r = -1;
    static char *page_info = NULL;


    page_info = opvp_alloc_string(&page_info, OPVP_INFO_PREFIX);
    page_info = opvp_cat_string(&page_info, opvp_gen_page_info(dev));


    if (printerContext != -1) {
        if (apiEntry->opvpStartPage)
            r = apiEntry->opvpStartPage(printerContext,
                       (opvp_char_t *)opvp_to_utf8(page_info));
        if (r != OPVP_OK) {
            ecode = -1;
        } else {
            ecode = InitGS();
        }
    }

    return ecode;
}
