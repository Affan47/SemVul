JumpIfInstanceTypeIsNotSequentialAscii(
    Register instance_type,
    Register scratch,
    Label* failure,
    Label::Distance near_jump) {
  if (!scratch.is(instance_type)) {
    movl(scratch, instance_type);
  }

  const int kFlatAsciiStringMask =
      kIsNotStringMask | kStringRepresentationMask | kStringEncodingMask;

  andl(scratch, Immediate(kFlatAsciiStringMask));
  cmpl(scratch, Immediate(kStringTag | kSeqStringTag | kAsciiStringTag));
  j(not_equal, failure, near_jump);
}
