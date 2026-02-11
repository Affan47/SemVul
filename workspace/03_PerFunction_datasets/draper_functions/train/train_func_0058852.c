giraffe_image_duplicate(const GiImage *self)
{

    GiImage *clone = NULL;


    if (self) {

        clone = giraffe_image_new(self->type);

        if (clone != NULL) {

            if (self->pixels != NULL) {
                cx_assert(self->type == cpl_image_get_type(self->pixels));
                clone->pixels = cpl_image_duplicate(self->pixels);
            }

            if (self->properties != NULL) {
                clone->properties =
                    cpl_propertylist_duplicate(self->properties);
            }

        }

    }

    return clone;

}
