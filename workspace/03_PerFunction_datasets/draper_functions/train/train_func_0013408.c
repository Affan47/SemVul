adjust_address_1 (rtx memref, enum machine_mode mode, HOST_WIDE_INT offset,
		  int validate, int adjust)
{
  rtx addr = XEXP (memref, 0);
  rtx new_rtx;
  rtx memoffset = MEM_OFFSET (memref);
  rtx size = 0;
  unsigned int memalign = MEM_ALIGN (memref);
  addr_space_t as = MEM_ADDR_SPACE (memref);
  enum machine_mode address_mode = targetm.addr_space.address_mode (as);
  int pbits;


  if (mode == GET_MODE (memref) && !offset
      && (!validate || memory_address_addr_space_p (mode, addr, as)))
    return memref;


  addr = copy_rtx (addr);


  pbits = GET_MODE_BITSIZE (address_mode);
  if (HOST_BITS_PER_WIDE_INT > pbits)
    {
      int shift = HOST_BITS_PER_WIDE_INT - pbits;
      offset = (((HOST_WIDE_INT) ((unsigned HOST_WIDE_INT) offset << shift))
		>> shift);
    }

  if (adjust)
    {


      if (GET_MODE (memref) != BLKmode && GET_CODE (addr) == LO_SUM
	  && offset >= 0
	  && (unsigned HOST_WIDE_INT) offset
	      < GET_MODE_ALIGNMENT (GET_MODE (memref)) / BITS_PER_UNIT)
	addr = gen_rtx_LO_SUM (address_mode, XEXP (addr, 0),
			       plus_constant (XEXP (addr, 1), offset));
      else
	addr = plus_constant (addr, offset);
    }

  new_rtx = change_address_1 (memref, mode, addr, validate);


  if (new_rtx == memref && offset != 0)
    new_rtx = copy_rtx (new_rtx);


  if (memoffset)
    memoffset = GEN_INT (offset + INTVAL (memoffset));


  if (offset != 0)
    memalign
      = MIN (memalign,
	     (unsigned HOST_WIDE_INT) (offset & -offset) * BITS_PER_UNIT);


  if (GET_MODE (new_rtx) != BLKmode)
    size = GEN_INT (GET_MODE_SIZE (GET_MODE (new_rtx)));
  else if (MEM_SIZE (memref))
    size = plus_constant (MEM_SIZE (memref), -offset);

  MEM_ATTRS (new_rtx) = get_mem_attrs (MEM_ALIAS_SET (memref), MEM_EXPR (memref),
				       memoffset, size, memalign, as,
				       GET_MODE (new_rtx));


  return new_rtx;
}
