enum_values_pack(int argc, VALUE *argv)
{
    if (argc == 0) return Qnil;
    if (argc == 1) return argv[0];
    return rb_ary_new4(argc, argv);
}
