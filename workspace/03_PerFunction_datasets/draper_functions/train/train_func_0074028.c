print_ref(size_t nx, size_t ny, size_t nz)
{
    uint8_t *array;

    if(NULL != (array = (uint8_t *)HDmalloc(nx * ny * nz))) {
        printf("Reference array:\n");
        init_full(array, nx, ny, nz);
        print_array(array, nx, ny, nz);
        HDfree(array);
    }
}
