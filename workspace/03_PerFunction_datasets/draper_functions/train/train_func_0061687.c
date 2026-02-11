rpdl_printer_initialize(gx_device_printer * pdev, FILE * prn_stream, int num_copies)
{
    gx_device_lprn *const lprn = (gx_device_lprn *) pdev;
    int xdpi = (int) pdev->x_pixels_per_inch;


    fprintf(prn_stream, "\033\022!@R00\033 ");
    fprintf(prn_stream, "\0334");
    fprintf(prn_stream, "\033\022YP,2 ");
    fprintf(prn_stream, "\033\022YB,2 ");
    fprintf(prn_stream, "\033\022YK,1 ");
    fprintf(prn_stream, "\033\022YL,1 ");
    fprintf(prn_stream, "\033\022YM,1 ");
    fprintf(prn_stream, "\033\022YQ,2 ");


    rpdl_paper_set(pdev, prn_stream);


    if (pdev->Duplex_set > 0) {
        if (pdev->Duplex) {
            fprintf(prn_stream, "\033\02261,");
            if (lprn->Tumble == 0)
                fprintf(prn_stream, "\033\022YA01,2 ");
            else
                fprintf(prn_stream, "\033\022YA01,1 ");
        } else
            fprintf(prn_stream, "\033\02260,");
    }


    switch(xdpi) {
    case 600:
      fprintf(prn_stream, "\033\022YA04,3 ");
      break;
    case 400:
      fprintf(prn_stream, "\033\022YA04,1 ");
      break;
    default:
      fprintf(prn_stream, "\033\022YA04,2 ");
      break;
    }


    switch(xdpi) {
    case 600:
      fprintf(prn_stream, "\033\022YW,3 ");
      break;
    case 400:
      fprintf(prn_stream, "\033\022YW,1 ");
      break;
    default:
      fprintf(prn_stream, "\033\022YW,2 ");
      break;
    }


    switch(xdpi) {
    case 600:
      fprintf(prn_stream, "\033\022Q5 ");
      break;
    case 400:
      fprintf(prn_stream, "\033\022Q4 ");
      break;
    default:
      fprintf(prn_stream, "\033\022Q0 ");
      break;
    }


    switch(xdpi) {
    case 600:
      fprintf(prn_stream, "\033\022#4 ");
      break;
    case 400:
      fprintf(prn_stream, "\033\022#2 ");
      break;
    }


    if (pdev->MediaSize[0] > pdev->MediaSize[1])
      fprintf(prn_stream, "\033\022D2 ");
    else
      fprintf(prn_stream, "\033\022D1 ");


    fprintf(prn_stream, "\033\022N%d ", num_copies);
}
