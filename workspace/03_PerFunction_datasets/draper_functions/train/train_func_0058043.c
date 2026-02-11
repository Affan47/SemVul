write_last_dim(csbe_context *cx, Array_table *array)
{
    int i;
    for (i = array->dim - 1; i >= 0; i--) {
        csbe_printf(cx, "[%d]", array->lim.ct[i]);
    }
}
