ossl_bn_coerce(VALUE self, VALUE other)
{
    switch(TYPE(other)) {
    case T_STRING:
	self = ossl_bn_to_s(0, NULL, self);
	break;
    case T_FIXNUM:
    case T_BIGNUM:
	self = ossl_bn_to_i(self);
	break;
    default:
	if (!RTEST(rb_obj_is_kind_of(other, cBN))) {
	    ossl_raise(rb_eTypeError, "Don't know how to coerce");
	}
    }
    return rb_assoc_new(other, self);
}
