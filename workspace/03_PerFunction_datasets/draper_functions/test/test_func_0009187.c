rb_num2dbl(VALUE val)
{
    switch (TYPE(val)) {
      case T_FLOAT:
	return RFLOAT_VALUE(val);

      case T_STRING:
	rb_raise(rb_eTypeError, "no implicit conversion to float from string");
	break;

      case T_NIL:
	rb_raise(rb_eTypeError, "no implicit conversion to float from nil");
	break;

      default:
	break;
    }

    return RFLOAT_VALUE(rb_Float(val));
}
