aarch64_add_offset (enum machine_mode mode, rtx temp, rtx reg, HOST_WIDE_INT offset)
{
  if (!aarch64_plus_immediate (GEN_INT (offset), mode))
    {
      rtx high;


      high = GEN_INT (offset);
      offset = 0;
      high = aarch64_force_temporary (mode, temp, high);
      reg = aarch64_force_temporary (mode, temp,
				     gen_rtx_PLUS (mode, high, reg));
    }
  return plus_constant (mode, reg, offset);
}
