next() {
  ASSERT(!done());


  while (pos_ > end_) {
    int tag = AdvanceGetTag();
    if (tag == kEmbeddedObjectTag) {
      ReadTaggedPC();
      if (SetMode(RelocInfo::EMBEDDED_OBJECT)) return;
    } else if (tag == kCodeTargetTag) {
      ReadTaggedPC();
      if (SetMode(RelocInfo::CODE_TARGET)) return;
    } else if (tag == kPositionTag) {
      ReadTaggedPC();
      Advance();

      if (mode_mask_ & RelocInfo::kPositionMask) {
        ReadTaggedData();
        if (SetMode(DebugInfoModeFromTag(GetPositionTypeTag()))) return;
      }
    } else {
      ASSERT(tag == kDefaultTag);
      int extra_tag = GetExtraTag();
      if (extra_tag == kPCJumpTag) {
        int top_tag = GetTopTag();
        if (top_tag == kVariableLengthPCJumpTopTag) {
          AdvanceReadVariableLengthPCJump();
        } else {
          AdvanceReadPC();
        }
      } else if (extra_tag == kDataJumpTag) {

        if (mode_mask_ & RelocInfo::kDebugMask) {
          int top_tag = GetTopTag();
          AdvanceReadData();
          if (SetMode(DebugInfoModeFromTag(top_tag))) return;
        } else {

          Advance(kIntptrSize);
        }
      } else {
        AdvanceReadPC();
        if (SetMode(static_cast<RelocInfo::Mode>(extra_tag))) return;
      }
    }
  }
  done_ = true;
}
