sockopt_unpack(VALUE self, VALUE template)
{
    return rb_funcall(sockopt_data(self), rb_intern("unpack"), 1, template);
}
