cpl_wcs_get_image_dims(const cpl_wcs *wcs) {


    cpl_ensure(wcs != NULL, CPL_ERROR_NULL_INPUT, NULL);

#ifdef CPL_WCS_INSTALLED


    return wcs->naxis == 0 ? NULL : wcs->imdims;

#else
    (void)cpl_error_set_(CPL_ERROR_NO_WCS);
    return NULL;
#endif
}
