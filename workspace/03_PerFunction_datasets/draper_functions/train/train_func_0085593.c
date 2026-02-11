_giraffe_slightsetup_new(cxint nslices)
{

    GiSLightSetup* self = cx_calloc(1, sizeof *self);

    if (self != NULL) {
        self->slices = cpl_matrix_new(nslices, 3);
    }

    return self;

}
