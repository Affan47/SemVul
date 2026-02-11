aarch64_pad_arg_upward (enum machine_mode mode, const_tree type)
{


  if (!BYTES_BIG_ENDIAN)
    return true;


  if (type
      ? (INTEGRAL_TYPE_P (type) || SCALAR_FLOAT_TYPE_P (type))
      : (SCALAR_INT_MODE_P (mode) || SCALAR_FLOAT_MODE_P (mode)))
    return false;


  return true;
}
