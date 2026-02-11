rtl_enan_ok (const uint32_t * label, size_t llen)
{
  bool en = false;
  bool an = false;
  const uint32_t *p;
  int bc;

  for (p = label + llen - 1; llen > 0; llen--, p--)
    {
      bc = uc_bidi_class (*p);
      switch (bc)
	{
	case UC_BIDI_EN:
	  en = true;
	  break;

	case UC_BIDI_AN:
	  an = true;
	  break;
	}
    }

  return !(en && an);
}
