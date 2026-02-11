thumb_legitimate_constant_p (enum machine_mode mode ATTRIBUTE_UNUSED, rtx x)
{
  return (GET_CODE (x) == CONST_INT
	  || GET_CODE (x) == CONST_DOUBLE
	  || CONSTANT_ADDRESS_P (x)
	  || flag_pic);
}
