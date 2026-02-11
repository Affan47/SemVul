img_from_gd2_partfname(klass, fname, srcx, srcy, w, h)
    VALUE klass, fname, srcx, srcy, w, h;
{
    VALUE f;
    FPTR_TYPE *fptr;
    gdImagePtr iptr;

    Check_Type(fname, T_STRING);

    f = rb_file_open(StringValuePtr(fname), "r");
    rb_io_binmode(f);
    GetOpenFile(f, fptr);
    rb_io_check_readable(fptr);

    iptr = gdImageCreateFromGd2Part(FILE_POINTER_FOR_CREATE_FROM, NUM2INT(srcx),
                                    NUM2INT(srcy), NUM2INT(w), NUM2INT(h));
    if (!iptr)
        rb_raise(rb_eArgError, "%s is not a valid Gd2 File", FPTR_PATH);

    return Data_Wrap_Struct(klass,0,free_img,iptr);
}
