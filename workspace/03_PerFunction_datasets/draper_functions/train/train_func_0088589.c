cpl_vector_set_size(cpl_vector * in, cpl_size newsize)
{

    cpl_ensure_code(in != NULL,  CPL_ERROR_NULL_INPUT);

    if (in->size != newsize) {
        cpl_ensure_code(newsize > 0, CPL_ERROR_ILLEGAL_INPUT);

        in->data = (double*)cpl_realloc(in->data,
                                        (size_t)newsize * sizeof(double));

        in->size = newsize;
    }

    return CPL_ERROR_NONE;

}
