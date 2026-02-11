H5O_delete_oh(H5F_t *f, hid_t dxpl_id, H5O_t *oh)
{
    H5O_mesg_t *curr_msg;
    unsigned	u;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(f);
    HDassert(oh);


    for(u = 0, curr_msg = &oh->mesg[0]; u < oh->nmesgs; u++, curr_msg++) {

        if(H5O_delete_mesg(f, dxpl_id, oh, curr_msg) < 0)
            HGOTO_ERROR(H5E_OHDR, H5E_CANTDELETE, FAIL, "unable to delete file space for object header message")
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
