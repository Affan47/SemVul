gdev_prn_close(gx_device * pdev)
{
    gx_device_printer * const ppdev = (gx_device_printer *)pdev;
    int code = 0;

    prn_finish_bg_print(ppdev);
    if (ppdev->bg_print.sema != NULL) {
        gx_semaphore_free(ppdev->bg_print.sema);
        ppdev->bg_print.sema = NULL;
    }
    gdev_prn_free_memory(pdev);
    if (ppdev->file != NULL) {
        code = gx_device_close_output_file(pdev, ppdev->fname, ppdev->file);
        ppdev->file = NULL;
    }
    return code;
}
