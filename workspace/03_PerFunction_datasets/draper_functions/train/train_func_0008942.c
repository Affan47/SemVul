strscan_concat(VALUE self, VALUE str)
{
    struct strscanner *p;

    GET_SCANNER(self, p);
    StringValue(str);
    rb_str_append(p->str, str);
    return self;
}
