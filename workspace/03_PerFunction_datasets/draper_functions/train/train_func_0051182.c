allocateUIntegerStorage(struct Input *in)
{
    hsize_t     len = 1;
    const char *err1 = "Unable to allocate dynamic memory.\n";
    const char *err2 = "Invalid storage size for unsigned integer input data.\n";
    int         j;

    for (j = 0; j < in->rank; j++)
        len *= in->sizeOfDimension[j];

    switch (in->inputSize) {
    case 8:
        if ((in->data = (VOIDP) HDmalloc((size_t) len * sizeof(H5DT_UINT8))) == NULL) {
            (void) HDfprintf(stderr, "%s", err1);
            return (-1);
        }
        break;

    case 16:
        if ((in->data = (VOIDP) HDmalloc((size_t) len * sizeof(H5DT_UINT16))) == NULL) {
            (void) HDfprintf(stderr, "%s", err1);
            return (-1);
        }
        break;

    case 32:
        if ((in->data = (VOIDP) HDmalloc((size_t) len * sizeof(H5DT_UINT32))) == NULL) {
            (void) HDfprintf(stderr, "%s", err1);
            return (-1);
        }
        break;

    case 64:
        if ((in->data = (VOIDP) HDmalloc((size_t) len * sizeof(H5DT_UINT64))) == NULL) {
            (void) HDfprintf(stderr, "%s", err1);
            return (-1);
        }
        break;

    default:
        (void) HDfprintf(stderr, "%s", err2);
        break;
    }
    return (0);
}
