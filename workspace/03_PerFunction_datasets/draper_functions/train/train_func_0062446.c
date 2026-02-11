opvp_beginpage(gx_device_vector *vdev)
{
    gx_device_opvp *pdev = (gx_device_opvp *)vdev;
    int code = -1;
    int ecode = 0;

#ifdef OPVP_IGNORE_BLANK_PAGE
    if (pdev->in_page) return 0;
#endif

    code = opvp_startpage((gx_device *)pdev);
    if (code) {
        ecode = code;
    } else {
        pdev->in_page = true;
        beginPage = true;
    }

    return ecode;
}
