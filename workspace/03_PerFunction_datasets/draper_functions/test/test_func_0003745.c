ATR_GetIntegerValue (ATR_t * atr, int name, BYTE * value)
{
  int ret;

  if (name == ATR_INTEGER_VALUE_FI)
    {
      if (atr->ib[0][ATR_INTERFACE_BYTE_TA].present)
	{
	  (*value) = (atr->ib[0][ATR_INTERFACE_BYTE_TA].value & 0xF0) >> 4;
	  ret = ATR_OK;
	}
      else
	ret = ATR_NOT_FOUND;
    }

  else if (name == ATR_INTEGER_VALUE_DI)
    {
      if (atr->ib[0][ATR_INTERFACE_BYTE_TA].present)
	{
	  (*value) = (atr->ib[0][ATR_INTERFACE_BYTE_TA].value & 0x0F);
	  ret = ATR_OK;
	}
      else
	ret = ATR_NOT_FOUND;
    }

  else if (name == ATR_INTEGER_VALUE_II)
    {
      if (atr->ib[0][ATR_INTERFACE_BYTE_TB].present)
	{
	  (*value) = (atr->ib[0][ATR_INTERFACE_BYTE_TB].value & 0x60) >> 5;
	  ret = ATR_OK;
	}
      else
	ret = ATR_NOT_FOUND;
    }

  else if (name == ATR_INTEGER_VALUE_PI1)
    {
      if (atr->ib[0][ATR_INTERFACE_BYTE_TB].present)
	{
	  (*value) = (atr->ib[0][ATR_INTERFACE_BYTE_TB].value & 0x1F);
	  ret = ATR_OK;
	}
      else
	ret = ATR_NOT_FOUND;
    }

  else if (name == ATR_INTEGER_VALUE_PI2)
    {
      if (atr->ib[1][ATR_INTERFACE_BYTE_TB].present)
	{
	  (*value) = atr->ib[1][ATR_INTERFACE_BYTE_TB].value;
	  ret = ATR_OK;
	}
      else
	ret = ATR_NOT_FOUND;
    }

  else if (name == ATR_INTEGER_VALUE_N)
    {
      if (atr->ib[0][ATR_INTERFACE_BYTE_TC].present)
	{
	  (*value) = atr->ib[0][ATR_INTERFACE_BYTE_TC].value;
	  ret = ATR_OK;
	}
      else
	ret = ATR_NOT_FOUND;
    }
  else
    ret = ATR_NOT_FOUND;

  return ret;
}
