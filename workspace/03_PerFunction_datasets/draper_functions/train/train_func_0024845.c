mca_io_ompio_get_fcoll_dynamic_constant_cbs (int *constant_cbs)
{
    int param;

    param = mca_base_var_find("ompi", "fcoll", "dynamic", "constant_cbs");
    if (param >= 0){
        const int *value = NULL;
        mca_base_var_get_value(param, &value, NULL, NULL);
        *constant_cbs = value[0];

	return OMPI_SUCCESS;
    }
    else{
	constant_cbs[0] = -1;
	return OMPI_SUCCESS;
    }

}
