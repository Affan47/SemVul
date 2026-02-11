kmclipm_image_save(const cpl_image *img,
                                  const char *filename,
                                  cpl_type_bpp bpp,
                                  const cpl_propertylist *pl,
                                  unsigned mode,
                                  double rej_val)
{
    cpl_error_code err      = CPL_ERROR_NONE;
    cpl_image      *img_dup = NULL;
    float          *pimg    = NULL;
    int            nx       = 0,
                   ny       = 0,
                   ix       = 0,
                   iy       = 0;

    KMCLIPM_TRY
    {

        KMCLIPM_TRY_CHECK_AUTOMSG(img != NULL,
                                  CPL_ERROR_NULL_INPUT);

        if ((rej_val != -1) || (kmclipm_is_nan_or_inf(rej_val))) {
            KMCLIPM_TRY_EXIT_IFN(
                img_dup = cpl_image_duplicate(img));

            KMCLIPM_TRY_EXIT_IFN(
                pimg = cpl_image_get_data(img_dup));
            nx = cpl_image_get_size_x(img_dup);
            ny = cpl_image_get_size_y(img_dup);
            for (iy = 0; iy < ny; iy++) {
                for (ix = 0; ix < nx; ix++) {
                    if (cpl_image_is_rejected(img_dup, ix+1, iy+1)) {
                        pimg[ix+iy*nx] = rej_val;
                    }
                }
            }

            err = cpl_image_save(img_dup, filename, bpp, pl, mode);
            KMCLIPM_TRY_CHECK_ERROR_STATE();

        } else {
            err = cpl_image_save(img, filename, bpp, pl, mode);
            KMCLIPM_TRY_CHECK_ERROR_STATE();
        }
    }
    KMCLIPM_CATCH
    {
        err = cpl_error_get_code();
    }

    cpl_image_delete(img_dup); img_dup = NULL;

    return err;
}
