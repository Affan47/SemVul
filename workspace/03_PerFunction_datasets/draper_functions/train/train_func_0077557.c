get_mem_attrs (alias, expr, offset, size, align, mode)
     HOST_WIDE_INT alias;
     tree expr;
     rtx offset;
     rtx size;
     unsigned int align;
     enum machine_mode mode;
{
  mem_attrs attrs;
  void **slot;


  if (alias == 0 && expr == 0 && offset == 0
      && (size == 0
	  || (mode != BLKmode && GET_MODE_SIZE (mode) == INTVAL (size)))
      && (STRICT_ALIGNMENT && mode != BLKmode
	  ? align == GET_MODE_ALIGNMENT (mode) : align == BITS_PER_UNIT))
    return 0;

  attrs.alias = alias;
  attrs.expr = expr;
  attrs.offset = offset;
  attrs.size = size;
  attrs.align = align;

  slot = htab_find_slot (mem_attrs_htab, &attrs, INSERT);
  if (*slot == 0)
    {
      *slot = ggc_alloc (sizeof (mem_attrs));
      memcpy (*slot, &attrs, sizeof (mem_attrs));
    }

  return *slot;
}
