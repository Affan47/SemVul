H5AC_term_interface(void)
{
    int	n = 0;

    FUNC_ENTER_NOAPI_NOINIT_NOERR

    if (H5_interface_initialize_g) {
#ifdef H5_HAVE_PARALLEL
        if(H5AC_dxpl_id > 0 || H5AC_ind_dxpl_id > 0) {

            n = 1;


            if(H5I_dec_ref(H5AC_dxpl_id) < 0 ||
                    H5I_dec_ref(H5AC_ind_dxpl_id) < 0)
                H5E_clear_stack(NULL);
            else {

                H5AC_dxpl_id = (-1);
                H5AC_ind_dxpl_id = (-1);


                H5_interface_initialize_g = 0;
            }
        }
        else
#else

            H5AC_dxpl_id=(-1);
            H5AC_ind_dxpl_id=(-1);
#endif

            H5_interface_initialize_g = 0;
    }

    FUNC_LEAVE_NOAPI(n)
}
