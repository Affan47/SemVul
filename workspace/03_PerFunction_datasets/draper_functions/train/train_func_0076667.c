img_from_xbm(klass, f)
    VALUE klass, f;
{
    FPTR_TYPE *fptr;
    gdImagePtr iptr;

    Check_Type(f, T_FILE);
    rb_io_binmode(f);
    GetOpenFile(f, fptr);
    rb_io_check_readable(fptr);

    iptr = gdImageCreateFromXbm(FILE_POINTER_FOR_CREATE_FROM);
    if (!iptr)
        rb_raise(rb_eArgError, "%s is not a valid Xbm File", FPTR_PATH);

    return Data_Wrap_Struct(klass,0,free_img,iptr);
}
