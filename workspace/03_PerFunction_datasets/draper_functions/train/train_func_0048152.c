H5O_msg_can_share(unsigned type_id, const void *mesg)
{
    const H5O_msg_class_t *type;
    htri_t ret_value;

    FUNC_ENTER_NOAPI_NOINIT_NOERR


    HDassert(type_id < NELMTS(H5O_msg_class_g));
    type = H5O_msg_class_g[type_id];
    HDassert(type);
    HDassert(mesg);


    if(type->can_share)
        ret_value = (type->can_share)(mesg);
    else {


        ret_value = (type->share_flags & H5O_SHARE_IS_SHARABLE) ? TRUE : FALSE;
    }


    HDassert((type->post_copy_file && type->copy_file) || ret_value == FALSE);

    FUNC_LEAVE_NOAPI(ret_value)
}
