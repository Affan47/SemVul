H5O_attr_exists_cb(H5O_t UNUSED *oh, H5O_mesg_t *mesg,
    unsigned UNUSED sequence, unsigned UNUSED *oh_modified, void *_udata)
{
    H5O_iter_rm_t *udata = (H5O_iter_rm_t *)_udata;
    herr_t ret_value = H5_ITER_CONT;

    FUNC_ENTER_NOAPI_NOINIT_NOERR


    HDassert(mesg);
    HDassert(!udata->found);


    if(HDstrcmp(((H5A_t *)mesg->native)->shared->name, udata->name) == 0) {

        udata->found = TRUE;


        ret_value = H5_ITER_STOP;
    }

    FUNC_LEAVE_NOAPI(ret_value)
}
