cdj_put_param_bpp(gx_device *pdev, gs_param_list *plist, int new_bpp,
  int real_bpp, int ccomps)
{
        if (new_bpp == 0 && ccomps == 0)
          return gdev_prn_put_params(pdev, plist);
        else
          {
                gx_device_color_info save_info;
                int save_bpp;
                int code;

                save_info = pdev->color_info;
                save_bpp = save_info.depth;
#define save_ccomps save_info.num_components
                if ( save_bpp == 8 && save_ccomps == 3 && !cprn_device->cmyk)
                  save_bpp = 3;
                code = cdj_set_bpp(pdev, real_bpp, ccomps);
                if ( code < 0 ) {
                  param_signal_error(plist, "BitsPerPixel", code);
                  param_signal_error(plist, "ProcessColorModel", code);
                  return code;
                }
                pdev->color_info.depth = new_bpp;
                code = gdev_prn_put_params(pdev, plist);
                if ( code < 0 )
                  {	cdj_set_bpp(pdev, save_bpp, save_ccomps);
                        return code;
                  }
                cdj_set_bpp(pdev, real_bpp, ccomps);
                if ((cdj->color_info.depth != save_bpp ||
                     (ccomps != 0 && ccomps != save_ccomps))
                    && pdev->is_open )
                  return gs_closedevice(pdev);
                return 0;
#undef save_ccomps
          }
}
