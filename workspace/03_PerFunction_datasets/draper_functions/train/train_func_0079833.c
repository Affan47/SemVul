load_from_image(VMG_ vm_obj_id_t self,
                                  const char *ptr, size_t siz)
{

    ext_ = (char *)ptr;


    if (siz < 8)
        err_throw(VMERR_INVAL_METACLASS_DATA);


    register_meta(vmg_ self);
}
