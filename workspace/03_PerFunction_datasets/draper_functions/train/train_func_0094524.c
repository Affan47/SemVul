SmiSub(Register dst,
                            Register src1,
                            Register src2,
                            Label* on_not_smi_result,
                            Label::Distance near_jump) {
  ASSERT_NOT_NULL(on_not_smi_result);
  ASSERT(!dst.is(src2));
  if (dst.is(src1)) {
    cmpq(dst, src2);
    j(overflow, on_not_smi_result, near_jump);
    subq(dst, src2);
  } else {
    movq(dst, src1);
    subq(dst, src2);
    j(overflow, on_not_smi_result, near_jump);
  }
}
