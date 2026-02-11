value_type_size(unsigned short value_type)
{
    int size = 0;

    switch(value_type)
    {
        case BYTE:
        case ASCII:
        case SBYTE:
        case UNDEFINED:
            size = 1;
            break;
        case SHORT:
        case SSHORT:
            size = 2;
            break;
        case LONG:
        case SLONG:
        case FLOAT:
            size = 4;
            break;
        case RATIONAL:
        case SRATIONAL:
        case DOUBLE:
            size = 8;
            break;
        default:
            break;
    }
    return(size);
}
