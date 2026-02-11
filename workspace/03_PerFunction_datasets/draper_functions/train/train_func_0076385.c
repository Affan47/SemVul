_giraffe_virtualslit_clear(GiVirtualSlit* self)
{

    if (self != NULL) {

        if (self->position != NULL) {
            cx_free(self->position);
            self->position = NULL;
        }

        if (self->signal != NULL) {
            cx_free(self->signal);
            self->signal = NULL;
        }

        if (self->variance != NULL) {
            cx_free(self->variance);
            self->variance = NULL;
        }

        if (self->fraction != NULL) {
            cx_free(self->fraction);
            self->fraction = NULL;
        }

        if (self->mask != NULL) {
            cx_free(self->mask);
            self->mask = NULL;
        }

        if (self->offset != NULL) {
            cx_free(self->offset);
            self->offset = NULL;
        }

        self->extra_width = 0.;
        self->center = 0.;
        self->width = 0;

    }

    return;

}
