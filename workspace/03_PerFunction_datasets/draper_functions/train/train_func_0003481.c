argf_inplace_mode_get(VALUE argf)
{
    if (!ARGF.inplace) return Qnil;
    return rb_str_new2(ARGF.inplace);
}
