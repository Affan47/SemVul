ShiftRightGF2Vec( Obj vec, UInt amount )
{
  UInt len;
  UInt *ptr1, *ptr2, *ptr0;
  UInt i;
  UInt block;
  UInt off;
  if (amount == 0)
    return;
  len = LEN_GF2VEC(vec);
  ResizeGF2Vec(vec, len+amount);
  if (amount % BIPEB == 0)
    {

      ptr1 = BLOCKS_GF2VEC(vec) + (len - 1 + amount)/BIPEB;
      ptr2 = ptr1 - amount/BIPEB;
      for (i = 0; i < (len + BIPEB - 1)/BIPEB; i++)
	*ptr1-- = *ptr2--;


      ptr2 = BLOCKS_GF2VEC(vec);
      while (ptr1 >= ptr2)
	*ptr1-- = 0;
    }
  else
    {
      ptr1 = BLOCKS_GF2VEC(vec) + (len -1 + amount)/BIPEB;
      ptr2 = ptr1 - amount/BIPEB;

      off = amount % BIPEB;
      ptr0 = BLOCKS_GF2VEC(vec);
      while (1)
	{
	  block = (*ptr2--) << off;
	  if (ptr2 < ptr0)
	    break;
	  block |= (*ptr2) >> (BIPEB - off);
	  *ptr1-- = block;
	}
      *ptr1-- = block;
      while (ptr1 >= ptr0)
	*ptr1-- = 0;
    }
  return;
}
