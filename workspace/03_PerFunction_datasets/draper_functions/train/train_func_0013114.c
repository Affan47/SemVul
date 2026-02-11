cpl_apertures_extract_mask(const cpl_image * self,
                                           const cpl_mask  * selection)
{
    cpl_errorstate  prestate = cpl_errorstate_get();
    cpl_apertures * aperts = NULL;
    cpl_size        nlabels;

    cpl_image     * labels = cpl_image_labelise_mask_create(selection,
                                                            &nlabels);

    if (labels != NULL && nlabels > 0) {


        aperts = cpl_apertures_new_from_image(self, labels);

    }

    if (aperts == NULL) {
        cpl_errorstate_is_equal(prestate)
            ? (void)cpl_error_set_(CPL_ERROR_DATA_NOT_FOUND)
            : (void)cpl_error_set_where_();
    }

    cpl_image_delete(labels);

    return aperts;
}
