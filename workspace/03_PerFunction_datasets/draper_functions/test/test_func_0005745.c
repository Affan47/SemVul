getarg(VMG_ uint argc)
{
    int idx;


    check_argc(vmg_ argc, 1);


    idx = pop_int_val(vmg0_);


    if (idx < 1 || idx > G_interpreter->get_cur_argc(vmg0_))
        err_throw(VMERR_BAD_VAL_BIF);


    *G_interpreter->get_r0() = *G_interpreter->get_param(vmg_ idx - 1);
}
