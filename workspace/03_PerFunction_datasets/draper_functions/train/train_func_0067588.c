infer_size(int *width_ptr, int *height_ptr, int size)
{
    int i;

    for(i=0;i<FF_ARRAY_ELEMS(sizes);i++) {
        if ((sizes[i][0] * sizes[i][1]) == size) {
            *width_ptr = sizes[i][0];
            *height_ptr = sizes[i][1];
            return 0;
        }
    }
    return -1;
}
