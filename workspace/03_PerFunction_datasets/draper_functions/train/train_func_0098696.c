giraffe_psfdata_contains(const GiPsfData* self, const cxchar* name)
{

    cx_map_const_iterator position;


    cx_assert(self != NULL);

    if (name == NULL) {
        return FALSE;
    }

    position = cx_map_find(self->values, name);

    if (position == cx_map_end(self->values)) {
        return FALSE;
    }

    return TRUE;

}
