giraffe_slitgeometry_set(GiSlitGeometry *self, cxint pos,
                         cpl_matrix *nm)
{

    if (self == NULL) {
        return;
    }

    if (self->subslits == NULL) {
        return;
    }

    if ((pos < 0) || (pos > self->nsubslits)) {
        return;
    }

    if (self->subslits[pos] != NULL) {
        cpl_matrix_delete(self->subslits[pos]);
    }

    if (nm) {
        self->subslits[pos] = cpl_matrix_duplicate(nm);
    }
    else {
        self->subslits[pos] = NULL;
    }

    return;

}
