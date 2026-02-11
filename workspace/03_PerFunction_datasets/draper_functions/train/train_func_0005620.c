pst_bitand(VALUE st1, VALUE st2)
{
    int status = PST2INT(st1) & NUM2INT(st2);

    return INT2NUM(status);
}
