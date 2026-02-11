pjxl_put_params(gx_device *pdev, gs_param_list *plist)
{	int printqual = pjxl->printqual;
        int rendertype = pjxl->rendertype;
        int bpp = 0, real_bpp = 0;
        int code = 0;

        code = cdj_put_param_int(plist, "PrintQuality", &printqual, -1, 1, code);
        code = cdj_put_param_int(plist, "RenderType", &rendertype, 0, 10, code);
        code = cdj_put_param_int(plist, "BitsPerPixel", &bpp, 1, 32, code);

        if ( code < 0 )
          return code;
        real_bpp = bpp;
        if ( rendertype > 0 )
          {

                if ( bpp > 0 && bpp < 16 )
                  real_bpp = 24;
          }
        code = cdj_put_param_bpp(pdev, plist, bpp, real_bpp, 0);
        if ( code < 0 )
          return code;

        pjxl->printqual = printqual;
        pjxl->rendertype = rendertype;
        return 0;
}
