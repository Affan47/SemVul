dbxout_fptype_value (type)
     tree type;
{
  char value = '0';
  enum machine_mode mode = TYPE_MODE (type);

  if (TREE_CODE (type) == REAL_TYPE)
    {
      if (mode == SFmode)
	value = '1';
      else if (mode == DFmode)
	value = '2';
      else if (mode == TFmode || mode == XFmode)
	value = '6';
      else

	value = '1';
    }
  else if (TREE_CODE (type) == COMPLEX_TYPE)
    {
      if (mode == SCmode)
	value = '3';
      else if (mode == DCmode)
	value = '4';
      else if (mode == TCmode || mode == XCmode)
	value = '5';
      else

	value = '3';
    }
  else
    abort ();

  putc (value, asmfile);
  CHARS (1);
}
