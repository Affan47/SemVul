write_short(ushort val)
{
 	if (ARCH_swap)
 		SWAP_short((short *)&val);
  if (fwrite(&val, sizeof(ushort), 1, arch_file) < 1)
    THROW("Write error");
}
