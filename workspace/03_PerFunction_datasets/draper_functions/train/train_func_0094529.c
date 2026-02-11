bfd_elf_perform_complex_relocation (bfd *input_bfd,
				    asection *input_section ATTRIBUTE_UNUSED,
				    bfd_byte *contents,
				    Elf_Internal_Rela *rel,
				    bfd_vma relocation)
{
  bfd_vma shift, x, mask;
  unsigned long start, oplen, len, wordsz, chunksz, lsb0_p, signed_p, trunc_p;
  bfd_reloc_status_type r;


  decode_complex_addend (&start, &oplen, &len, &wordsz,
			 &chunksz, &lsb0_p, &signed_p,
			 &trunc_p, rel->r_addend);

  mask = (((1L << (len - 1)) - 1) << 1) | 1;

  if (lsb0_p)
    shift = (start + 1) - len;
  else
    shift = (8 * wordsz) - (start + len);


  x = get_value (wordsz, chunksz, input_bfd, contents + rel->r_offset);

#ifdef DEBUG
  printf ("Doing complex reloc: "
	  "lsb0? %ld, signed? %ld, trunc? %ld, wordsz %ld, "
	  "chunksz %ld, start %ld, len %ld, oplen %ld\n"
	  "    dest: %8.8lx, mask: %8.8lx, reloc: %8.8lx\n",
	  lsb0_p, signed_p, trunc_p, wordsz, chunksz, start, len,
	  oplen, (unsigned long) x, (unsigned long) mask,
	  (unsigned long) relocation);
#endif

  r = bfd_reloc_ok;
  if (! trunc_p)

    r = bfd_check_overflow ((signed_p
			     ? complain_overflow_signed
			     : complain_overflow_unsigned),
			    len, 0, (8 * wordsz),
			    relocation);


  x = (x & ~(mask << shift)) | ((relocation & mask) << shift);

#ifdef DEBUG
  printf ("           relocation: %8.8lx\n"
	  "         shifted mask: %8.8lx\n"
	  " shifted/masked reloc: %8.8lx\n"
	  "               result: %8.8lx\n",
	  (unsigned long) relocation, (unsigned long) (mask << shift),
	  (unsigned long) ((relocation & mask) << shift), (unsigned long) x);
#endif

  put_value (wordsz, chunksz, input_bfd, x, contents + rel->r_offset);
  return r;
}
