_giraffe_virtualslit_setup(GiVirtualSlit* self, cxint bin,
                           cxdouble center, cxdouble width,
                           const cpl_image* signal, const cpl_image* variance,
                           const cpl_image* bpixel)
{

    register cxint ny = cpl_image_get_size_x(signal);
    register cxint offset = bin * cpl_image_get_size_x(signal);

    register cxdouble lower = center - (width + self->extra_width);
    register cxdouble upper = center + (width + self->extra_width);

    register cxint first = (cxint) floor(lower);
    register cxint last = (cxint) ceil(upper);

    const cxdouble* s = cpl_image_get_data_double_const(signal);
    const cxdouble* v = cpl_image_get_data_double_const(variance);


    lower = CX_MAX(0., lower);
    upper = CX_MIN(ny, upper);

    first = CX_MAX(0, first);
    last = CX_MIN(ny, last);

    self->center = center;
    self->width = last - first + 1;


    _giraffe_virtualslit_allocate(self);

    if (bpixel != NULL) {

        register cxint k = 0;
        register cxint y = 0;

        const cxint* _bpixel = cpl_image_get_data_int_const(bpixel);


        for (y = first; y <= last; y++) {

            register cxint ypos = offset + y;

            cxint ok = (_bpixel[ypos] & GIR_M_PIX_SET) == 0 ? 1 : 0;


            self->position[k] = y - center;
            self->fraction[k]  = 1.;

            self->signal[k] = s[ypos];
            self->variance[k] = v[ypos];

            self->mask[k] = ok;
            self->offset[k] = ypos;
            ++k;

        }

    }
    else {

        register cxint k = 0;
        register cxint y = 0;


        for (y = first; y <= last; y++) {

            register cxint ypos = offset + y;

            cxint ok = 1;


            self->position[k] = y - center;
            self->fraction[k]  = 1.;

            self->signal[k] = s[ypos];
            self->variance[k] = v[ypos];

            self->mask[k] = ok;
            self->offset[k] = ypos;
            ++k;

        }

    }


    self->fraction[0] = ((cxdouble)first + 1.) - lower;
    self->fraction[self->width - 1] = upper - ((cxdouble)last - 1.);

    return self->width;

}
