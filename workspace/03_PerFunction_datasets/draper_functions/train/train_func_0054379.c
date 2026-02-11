H5SL_search(H5SL_t *slist, const void *key)
{
    H5SL_node_t *x;
    uint32_t hashval = 0;
    void *ret_value;

    FUNC_ENTER_NOAPI_NOINIT_NOFUNC(H5SL_search);


    assert(slist);
    assert(key);


    x=slist->header;
    switch(slist->type) {
        case H5SL_TYPE_INT:
            H5SL_SEARCH(SCALAR, slist, x, const int, key, -)
            break;

        case H5SL_TYPE_HADDR:
            H5SL_SEARCH(SCALAR, slist, x, const haddr_t, key, -)
            break;

        case H5SL_TYPE_STR:
            H5SL_SEARCH(STRING, slist, x, char *, key, hashval)
            break;

        case H5SL_TYPE_HSIZE:
            H5SL_SEARCH(SCALAR, slist, x, const hsize_t, key, -)
            break;

        case H5SL_TYPE_UNSIGNED:
            H5SL_SEARCH(SCALAR, slist, x, const unsigned, key, -)
            break;

        case H5SL_TYPE_SIZE:
            H5SL_SEARCH(SCALAR, slist, x, const size_t, key, -)
            break;

        case H5SL_TYPE_OBJ:
            H5SL_SEARCH(OBJ, slist, x, const H5_obj_t, key, -)
            break;

        default:
            HDassert(0 && "Unknown skiplist type!");
    }


    ret_value=NULL;

done:
    FUNC_LEAVE_NOAPI(ret_value);
}
