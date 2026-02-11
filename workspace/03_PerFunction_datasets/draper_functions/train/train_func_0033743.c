Write(const RelocInfo* rinfo) {
#ifdef DEBUG
  byte* begin_pos = pos_;
#endif
  Counters::reloc_info_count.Increment();
  ASSERT(rinfo->pc() - last_pc_ >= 0);
  ASSERT(RelocInfo::NUMBER_OF_MODES < kMaxRelocModes);

  uint32_t pc_delta = static_cast<uint32_t>(rinfo->pc() - last_pc_);
  RelocInfo::Mode rmode = rinfo->rmode();


  if (rmode == RelocInfo::EMBEDDED_OBJECT) {
    WriteTaggedPC(pc_delta, kEmbeddedObjectTag);
  } else if (rmode == RelocInfo::CODE_TARGET) {
    WriteTaggedPC(pc_delta, kCodeTargetTag);
  } else if (RelocInfo::IsPosition(rmode)) {

    intptr_t data_delta = rinfo->data() - last_data_;
    int pos_type_tag = rmode == RelocInfo::POSITION ? kNonstatementPositionTag
                                                    : kStatementPositionTag;


    if (data_delta >= -(1 << (kSmallDataBits-1)) &&
        data_delta < 1 << (kSmallDataBits-1)) {
      WriteTaggedPC(pc_delta, kPositionTag);
      WriteTaggedData(data_delta, pos_type_tag);
      last_data_ = rinfo->data();
    } else {

      WriteExtraTaggedPC(pc_delta, kPCJumpTag);
      WriteExtraTaggedData(data_delta, pos_type_tag);
      last_data_ = rinfo->data();
    }
  } else if (RelocInfo::IsComment(rmode)) {

    WriteExtraTaggedPC(pc_delta, kPCJumpTag);
    WriteExtraTaggedData(rinfo->data() - last_data_, kCommentTag);
    last_data_ = rinfo->data();
  } else {


    ASSERT(rmode < kPCJumpTag && rmode < kDataJumpTag);
    WriteExtraTaggedPC(pc_delta, rmode);
  }
  last_pc_ = rinfo->pc();
#ifdef DEBUG
  ASSERT(begin_pos - pos_ <= kMaxSize);
#endif
}
