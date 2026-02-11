Generate() {


    if (ensure_reloc_space_) {
      codegen_->masm()->RecordComment(RelocInfo::kFillerCommentString, true);
    }
    codegen_->RecordSafepoint(pointers_, deoptimization_index_);
  }
