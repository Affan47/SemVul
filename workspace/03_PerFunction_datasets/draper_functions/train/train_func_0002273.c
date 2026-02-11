hdrl_image_get_pixel(const hdrl_image * self,
                            cpl_size xpos, cpl_size ypos,
                            double * error, int * pis_rejected)
{
    int d;
    double v = cpl_image_get(self->image, xpos, ypos, &d);


    if (pis_rejected) {
        *pis_rejected = d;
    }

    if (error) {
        *error = cpl_image_get(self->error, xpos, ypos, &d);
    }

    return v;
}
