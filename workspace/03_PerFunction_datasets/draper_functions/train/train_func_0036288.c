create_comm(int target_keyval, bool want_inherit)
{
    int err;
    int keyval;
    ompi_attribute_fn_ptr_union_t copy;
    ompi_attribute_fn_ptr_union_t del;

    keyval = -1;
    copy.attr_communicator_copy_fn = (MPI_Comm_internal_copy_attr_function*)
        (want_inherit ? MPI_COMM_DUP_FN : MPI_COMM_NULL_COPY_FN);
    del.attr_communicator_delete_fn = MPI_COMM_NULL_DELETE_FN;
    err = ompi_attr_create_keyval(COMM_ATTR, copy, del,
                                  &keyval, NULL, OMPI_KEYVAL_PREDEFINED, NULL);
    if (MPI_SUCCESS != err) {
        return err;
    }
    if (target_keyval != keyval) {
        return OMPI_ERR_BAD_PARAM;
    }
    return OMPI_SUCCESS;
}
