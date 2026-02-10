H5Tinsert(hid_t parent_id, const char *name, size_t offset, hid_t member_id)
{
    H5T_t	*parent;
    H5T_t	*member;
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE4("e", "i*szi", parent_id, name, offset, member_id);


    if(parent_id == member_id)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "can't insert compound datatype within itself")
    if(NULL == (parent = (H5T_t *)H5I_object_verify(parent_id, H5I_DATATYPE)) || H5T_COMPOUND != parent->shared->type)
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a compound datatype")
    if(H5T_STATE_TRANSIENT != parent->shared->state)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "parent type read-only")
    if(!name || !*name)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "no member name")
    if(NULL == (member = (H5T_t *)H5I_object_verify(member_id, H5I_DATATYPE)))
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a datatype")


    if(H5T__insert(parent, name, offset, member) < 0)
        HGOTO_ERROR(H5E_DATATYPE, H5E_CANTINSERT, FAIL, "unable to insert member")

done:
    FUNC_LEAVE_API(ret_value)
}
