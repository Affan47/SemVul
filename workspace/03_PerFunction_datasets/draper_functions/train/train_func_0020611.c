_giraffe_wlresiduals_get(const GiWlResiduals *self, cxsize idx)
{

    cx_map_const_iterator position;

    GiWlResidualData *data = NULL;


    position = cx_map_begin(self->data);

    if (position == cx_map_end(self->data)) {
        return NULL;
    }

    if (idx > 0) {

        cxsize i;

        for (i = 1; i < idx; i++) {
            position = cx_map_next(self->data, position);
        }

    }

    data = cx_map_get_value(self->data, position);

    return data;

}
