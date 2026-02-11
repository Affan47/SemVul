get_coll_addsub_rhs_ele_cnt(VMG0_) const
{

    switch(typ)
    {
    case VM_LIST:

        return vmb_get_len(G_const_pool->get_ptr(val.ofs));

    case VM_OBJ:

        return vm_objp(vmg_ val.obj)->get_coll_addsub_rhs_ele_cnt(vmg0_);

    default:

        return 1;
    }
}
