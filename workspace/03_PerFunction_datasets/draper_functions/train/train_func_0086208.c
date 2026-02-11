cpl_apertures_extract_window(const cpl_image  * self,
                                             const cpl_vector * sigmas,
                                             cpl_size           llx,
                                             cpl_size           lly,
                                             cpl_size           urx,
                                             cpl_size           ury,
                                             cpl_size         * pisigma)
{
    cpl_apertures * aperts;
    cpl_image     * extracted;
    cpl_size        i;


    cpl_ensure(self != NULL,     CPL_ERROR_NULL_INPUT, NULL);
    cpl_ensure(sigmas != NULL, CPL_ERROR_NULL_INPUT, NULL);


    extracted = cpl_image_extract(self, llx, lly, urx, ury);
    cpl_ensure(extracted, cpl_error_get_code(), NULL);


    aperts = cpl_apertures_extract(extracted, sigmas, pisigma);
    cpl_image_delete(extracted);
    cpl_ensure(aperts, cpl_error_get_code(), NULL);


    for (i = 0; i < aperts->naperts; i++) {
        aperts->x[i] += (double)(llx - 1);
        aperts->y[i] += (double)(lly - 1);
        aperts->maxpos_x[i] += (double)(llx - 1);
        aperts->maxpos_y[i] += (double)(lly - 1);
        aperts->minpos_x[i] += (double)(llx - 1);
        aperts->minpos_y[i] += (double)(lly - 1);
        aperts->xcentroid[i] += (double)(llx - 1);
        aperts->ycentroid[i] += (double)(lly - 1);
        aperts->left_x[i] += llx - 1;
        aperts->left_y[i] += lly - 1;
        aperts->right_x[i] += llx - 1;
        aperts->right_y[i] += lly - 1;
        aperts->top_x[i] += llx - 1;
        aperts->top_y[i] += lly - 1;
        aperts->bottom_x[i] += llx - 1;
        aperts->bottom_y[i] += lly - 1;
    }

    return aperts;
}
