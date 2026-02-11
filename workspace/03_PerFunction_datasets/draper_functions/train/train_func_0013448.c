H5O_shared_decode(H5F_t *f, hid_t dxpl_id, H5O_t *open_oh, unsigned *ioflags,
    const uint8_t *buf, const H5O_msg_class_t *type)
{
    H5O_shared_t sh_mesg;
    unsigned version;
    void *ret_value;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(f);
    HDassert(buf);
    HDassert(type);


    version = *buf++;
    if(version < H5O_SHARED_VERSION_1 || version > H5O_SHARED_VERSION_LATEST)
        HGOTO_ERROR(H5E_OHDR, H5E_CANTLOAD, NULL, "bad version number for shared object message")


    if(version >= H5O_SHARED_VERSION_2)
        sh_mesg.type = *buf++;
    else {
        sh_mesg.type = H5O_SHARE_TYPE_COMMITTED;
        buf++;
    }


    if(version == H5O_SHARED_VERSION_1)
        buf += 6;


    if(version == H5O_SHARED_VERSION_1) {

        sh_mesg.u.loc.index = 0;


        buf += H5F_SIZEOF_SIZE(f);
        H5F_addr_decode(f, &buf, &(sh_mesg.u.loc.oh_addr));
    }
    else if (version >= H5O_SHARED_VERSION_2) {


        if(sh_mesg.type == H5O_SHARE_TYPE_SOHM) {
            HDassert(version >= H5O_SHARED_VERSION_3);
            HDmemcpy(&sh_mesg.u.heap_id, buf, sizeof(sh_mesg.u.heap_id));
        }
        else {


            if(version < H5O_SHARED_VERSION_3)
                sh_mesg.type = H5O_SHARE_TYPE_COMMITTED;

            sh_mesg.u.loc.index = 0;
            H5F_addr_decode(f, &buf, &sh_mesg.u.loc.oh_addr);
        }
    }


    sh_mesg.file = f;
    sh_mesg.msg_type_id = type->id;


    if(NULL == (ret_value = H5O_shared_read(f, dxpl_id, open_oh, ioflags, &sh_mesg, type)))
        HGOTO_ERROR(H5E_OHDR, H5E_READERROR, NULL, "unable to retrieve native message")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
