op_print_obj(void)
{
  offset short_name_off = object_name(operand[0]);
  if(short_name_off)
    decodezscii(short_name_off, output_char);
  else
    n_show_error(E_OBJECT, "attempt to print name of nameless object", operand[0]);
}
