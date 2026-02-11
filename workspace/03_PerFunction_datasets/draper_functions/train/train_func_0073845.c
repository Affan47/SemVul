DFKInoset(VOIDP source, VOIDP dest, uint32 num_elm,
          uint32 source_stride, uint32 dest_stride)
{
    CONSTR(FUNC, "DFKInoset");

    HEclear();


    source = source;
    dest = dest;
    num_elm = num_elm;
    source_stride = source_stride;
    dest_stride = dest_stride;


    HERROR(DFE_BADCONV);
    return FAIL;
}
