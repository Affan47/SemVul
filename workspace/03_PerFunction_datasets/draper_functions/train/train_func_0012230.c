H5T_pack(const H5T_t *dt)
{
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT

    HDassert(dt);

    if(H5T_detect_class(dt, H5T_COMPOUND, FALSE) > 0) {

        if(TRUE == H5T_is_packed(dt))
            HGOTO_DONE(SUCCEED)


        if(H5T_STATE_TRANSIENT != dt->shared->state)
            HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "datatype is read-only")

        if(dt->shared->parent) {
            if (H5T_pack(dt->shared->parent) < 0)
                HGOTO_ERROR(H5E_DATATYPE, H5E_CANTINIT, FAIL, "unable to pack parent of datatype")


            if(dt->shared->type == H5T_ARRAY)
                dt->shared->size = dt->shared->parent->shared->size * dt->shared->u.array.nelem;
            else if(dt->shared->type != H5T_VLEN)
                dt->shared->size = dt->shared->parent->shared->size;
        }
        else if(dt->shared->type == H5T_COMPOUND) {
            size_t	offset;
            unsigned i;


            for(i = 0; i < dt->shared->u.compnd.nmembs; i++) {
                if(H5T_pack(dt->shared->u.compnd.memb[i].type) < 0)
                    HGOTO_ERROR(H5E_DATATYPE, H5E_CANTINIT, FAIL, "unable to pack part of a compound datatype")


                dt->shared->u.compnd.memb[i].size = (dt->shared->u.compnd.memb[i].type)->shared->size;
            }


            if(H5T__sort_value(dt, NULL) < 0)
		HGOTO_ERROR(H5E_INTERNAL, H5E_CANTCOMPARE, FAIL, "value sort failed")
            for(i = 0, offset = 0; i < dt->shared->u.compnd.nmembs; i++) {
                dt->shared->u.compnd.memb[i].offset = offset;
                offset += dt->shared->u.compnd.memb[i].size;
            }


            dt->shared->size = MAX(1, offset);


            dt->shared->u.compnd.packed = TRUE;
        }
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
