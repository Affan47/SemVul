ADIOI_End_call(MPI_Comm comm, int keyval, void *attribute_val, void
		  *extra_state)
{
    int error_code;

    ADIOI_UNREFERENCED_ARG(comm);
    ADIOI_UNREFERENCED_ARG(attribute_val);
    ADIOI_UNREFERENCED_ARG(extra_state);

    MPI_Keyval_free(&keyval);


    if (ADIOI_cb_config_list_keyval != MPI_KEYVAL_INVALID)
        MPI_Keyval_free(&ADIOI_cb_config_list_keyval);

    ADIO_End(&error_code);
    return error_code;
}
