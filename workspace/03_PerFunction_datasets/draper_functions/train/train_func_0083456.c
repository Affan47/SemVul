jl_new_array(jl_type_t *atype, jl_tuple_t *dims)
{
    size_t ndims = dims->length;
    size_t *adims = alloca(ndims*sizeof(size_t));
    size_t i;
    for(i=0; i < ndims; i++)
        adims[i] = jl_unbox_long(jl_tupleref(dims,i));
    return _new_array(atype, ndims, adims);
}
