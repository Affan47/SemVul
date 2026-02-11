escpage_print_page_copies(gx_device_printer * pdev, FILE * fp, int num_coipes)
{
    gx_device_lprn *const lprn = (gx_device_lprn *) pdev;

    if (pdev->PageCount == 0) {
        double xDpi = pdev->x_pixels_per_inch;


        fputs(epson_remote_start, fp);
        fprintf(fp, "@EJL SELECT LANGUAGE=ESC/PAGE\r\n");


        if (lprn->RITOff)
            fprintf(fp, "@EJL SET RI=OFF\r\n");
        else
            fprintf(fp, "@EJL SET RI=ON\r\n");


        fprintf(fp, "@EJL SET RS=%s\r\n", xDpi > 300 ? "FN" : "QK");
        fprintf(fp, "@EJL ENTER LANGUAGE=ESC/PAGE\r\n");
    }
    return lp2000_print_page_copies(pdev, fp, num_coipes);
}
