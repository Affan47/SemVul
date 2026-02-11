getp_upper(VMG_ vm_val_t *retval, const vm_val_t *self_val,
                             const char *str, uint *argc)
{
    size_t srclen;
    size_t dstlen;
    size_t rem;
    utf8_ptr srcp;
    utf8_ptr dstp;
    vm_obj_id_t result_obj;
    static CVmNativeCodeDesc desc(0);


    if (get_prop_check_argc(retval, argc, &desc))
        return TRUE;


    srclen = vmb_get_len(str);


    G_stk->push(self_val);


    for (dstlen = 0, srcp.set((char *)str + VMB_LEN), rem = srclen ;
         rem != 0 ; srcp.inc(&rem))
    {

        dstlen += utf8_ptr::s_wchar_size(t3_to_upper(srcp.getch()));
    }


    result_obj = CVmObjString::create(vmg_ FALSE, dstlen);


    dstp.set(((CVmObjString *)vm_objp(vmg_ result_obj))->cons_get_buf());


    for (srcp.set((char *)str + VMB_LEN), rem = srclen ;
         rem != 0 ; srcp.inc(&rem))
    {

        dstp.setch(t3_to_upper(srcp.getch()));
    }


    retval->set_obj(result_obj);


    G_stk->discard();


    return TRUE;
}
