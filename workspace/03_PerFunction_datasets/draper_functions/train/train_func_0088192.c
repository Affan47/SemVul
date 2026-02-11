Branch(Condition cc, Hint hint) {
  ASSERT(cgen()->has_valid_frame());

  int count = cgen()->frame()->height() - expected_height_;
  if (count > 0) {


    JumpTarget fall_through;


    fall_through.Branch(NegateCondition(cc), NegateHint(hint));
    Jump();
    fall_through.Bind();
  } else {
    DoBranch(cc, hint);
  }
}
