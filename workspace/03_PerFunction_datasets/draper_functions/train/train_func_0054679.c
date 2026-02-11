compare(VMG_ size_t a, size_t b)
{
    int result;
    vm_val_t val_a;
    vm_val_t val_b;


    get_ele(vmg_ a, &val_a);
    get_ele(vmg_ b, &val_b);


    if (compare_fn_.typ != VM_NIL)
    {
        vm_val_t val;


        G_stk->push(&val_b);
        G_stk->push(&val_a);


        G_interpreter->call_func_ptr(vmg_ &compare_fn_, 2, "sort.compare", 0);


        val = *G_interpreter->get_r0();


        if (val.typ != VM_INT)
            err_throw(VMERR_INT_VAL_REQD);


        result = val.val.intval;
    }
    else
    {

        result = val_a.compare_to(vmg_ &val_b);
    }


    if (descending_)
        result = -result;


    return result;
}
