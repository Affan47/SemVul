igor_data_type_size(IgorDataType type)
{
    IgorDataType basetype;
    gsize size;

    basetype = type & ~(IGOR_UNSIGNED | IGOR_COMPLEX);
    if (basetype == IGOR_SINGLE || basetype == IGOR_INT32)
        size = 4;
    else if (basetype == IGOR_INT16)
        size = 2;
    else if (basetype == IGOR_DOUBLE)
        size = 8;
    else if (basetype == IGOR_INT8)
        size = 1;
    else
        return 0;


    if ((type & IGOR_UNSIGNED)
        && (basetype == IGOR_DOUBLE || basetype == IGOR_SINGLE))
        return 0;

    if (type & IGOR_COMPLEX)
        size *= 2;

    return size;
}
