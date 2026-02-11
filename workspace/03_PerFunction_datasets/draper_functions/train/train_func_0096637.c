UD_cb_query(const char * link_name, const void *udata, size_t udata_size,
    void *buf, size_t buf_size)
{
    if(!link_name) TEST_ERROR
    if(udata_size > 0 && !udata) TEST_ERROR

    if(HDstrcmp(link_name, UD_CB_LINK_NAME)) TEST_ERROR
    if(HDstrcmp((const char *)udata, UD_CB_TARGET)) TEST_ERROR
    if(udata_size != UD_CB_TARGET_LEN) TEST_ERROR

    if(buf) {
      if(buf_size < 16) TEST_ERROR
      HDstrcpy((char *)buf, "query succeeded");
    }


    return 16;

error:
    return -1;
}
