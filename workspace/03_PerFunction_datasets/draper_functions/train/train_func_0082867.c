setup_getp_retval(VMG_ vm_obj_id_t self,
                                    vm_val_t *retval, char **new_ext,
                                    size_t prec)
{

    if (is_nan(ext_))
    {
        retval->set_obj(self);
        return TRUE;
    }


    G_stk->push()->set_obj(self);


    retval->set_obj(create(vmg_ FALSE, prec));
    *new_ext = get_objid_ext(vmg_ retval->val.obj);


    return FALSE;
}
