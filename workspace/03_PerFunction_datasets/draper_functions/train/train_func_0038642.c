SmiNeg(Register dst,
                            Register src,
                            Label* on_smi_result,
                            Label::Distance near_jump) {
  if (dst.is(src)) {
    ASSERT(!dst.is(kScratchRegister));
    movq(kScratchRegister, src);
    neg(dst);

    cmpq(dst, kScratchRegister);
    j(not_equal, on_smi_result, near_jump);
    movq(src, kScratchRegister);
  } else {
    movq(dst, src);
    neg(dst);
    cmpq(dst, src);

    j(not_equal, on_smi_result, near_jump);
  }
}
