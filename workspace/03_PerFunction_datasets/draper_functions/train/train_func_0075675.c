set_field_pad(FIELD  * field, int ch)
{
  int res = E_BAD_ARGUMENT;

  Normalize_Field( field );
  if (isprint((unsigned char)ch))
    {
      if (field->pad != ch)
	{
	  field->pad = ch;
	  res = _nc_Synchronize_Attributes( field );
	}
      else
	res = E_OK;
    }
  RETURN(res);
}
