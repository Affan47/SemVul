H5E_get_class_name(const H5E_cls_t *cls, char *name, size_t size)
{
    ssize_t       len;

    FUNC_ENTER_NOAPI_NOINIT_NOERR


    HDassert(cls);


    len = (ssize_t)HDstrlen(cls->cls_name);


    if(name) {
       HDstrncpy(name, cls->cls_name, MIN((size_t)(len + 1), size));
       if((size_t)len >= size)
          name[size - 1] = '\0';
    }


    FUNC_LEAVE_NOAPI(len)
}
