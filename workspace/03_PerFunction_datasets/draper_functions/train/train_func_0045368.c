SmiShiftLeft(Register dst,
                                  Register src1,
                                  Register src2) {
  ASSERT(!dst.is(rcx));
  NearLabel result_ok;

  if (!dst.is(src1)) {
    movq(dst, src1);
  }
  SmiToInteger32(rcx, src2);

  and_(rcx, Immediate(0x1f));
  shl_cl(dst);
}
