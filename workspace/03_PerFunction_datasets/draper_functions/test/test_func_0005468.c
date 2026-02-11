cdnj500_start_raster_mode(gx_device_printer * pdev, int paper_size,
                         FILE * prn_stream)
{

    int xres = cdj850->x_pixels_per_inch;
    int yres = cdj850->y_pixels_per_inch;
    float x = pdev->width  / pdev->x_pixels_per_inch * 10;
    float y = pdev->height / pdev->y_pixels_per_inch * 10;


    fprintf(prn_stream, "\033%%-12345X");


    fprintf(prn_stream, "@PJL JOB NAME=\"GS %.2fx%.2f\" \n", x * 2.54, y * 2.54);


    fprintf(prn_stream, "@PJL SET RENDERMODE = COLOR \n");


    fprintf(prn_stream, "@PJL SET COLORSPACE = SRGB \n");


    if (cdj850->quality == DRAFT) {
        fprintf(prn_stream, "@PJL SET RENDERINTENT = PERCEPTUAL \n");
        fprintf(prn_stream, "@PJL SET RET = ON \n");
        fprintf(prn_stream, "@PJL SET MAXDETAIL = OFF \n");
    } else if (cdj850->quality == NORMAL) {
        fprintf(prn_stream, "@PJL SET RENDERINTENT = PERCEPTUAL \n");
        fprintf(prn_stream, "@PJL SET RET = ON \n");
        fprintf(prn_stream, "@PJL SET MAXDETAIL = ON \n");
    } else {
        fprintf(prn_stream, "@PJL SET RENDERINTENT = PERCEPTUAL \n");
        fprintf(prn_stream, "@PJL SET RET = OFF \n");
        fprintf(prn_stream, "@PJL SET MAXDETAIL = ON \n");
    }


    fprintf(prn_stream, "@PJL ENTER LANGUAGE=PCL3GUI \n");


    fprintf(prn_stream, "\033*o%dM", cdj850->quality);


    fprintf(prn_stream, "\033&u%dD", (int)xres);

    return;
}
