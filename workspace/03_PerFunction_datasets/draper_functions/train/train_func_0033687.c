H5E_dump_api_stack(int is_api)
{
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)


    if(is_api) {
        H5E_t *estack = H5E_get_my_stack();

        HDassert(estack);

#ifdef H5_NO_DEPRECATED_SYMBOLS
            if(estack->auto_op.func2)
                (void)((estack->auto_op.func2)(H5E_DEFAULT, estack->auto_data));
#else
        if(estack->auto_op.vers == 1) {
            if(estack->auto_op.func1)
                (void)((estack->auto_op.func1)(estack->auto_data));
        }
        else {
            if(estack->auto_op.func2)
                (void)((estack->auto_op.func2)(H5E_DEFAULT, estack->auto_data));
        }
#endif
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
