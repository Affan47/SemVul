CompactMemTable() {
  mutex_.AssertHeld();
  assert(imm_ != NULL);


  VersionEdit edit;
  Version* base = versions_->current();
  base->Ref();
  Status s = WriteLevel0Table(imm_, &edit, base);
  base->Unref();

  if (s.ok() && shutting_down_.Acquire_Load()) {
    s = Status::IOError("Deleting DB during memtable compaction");
  }


  if (s.ok()) {
    edit.SetPrevLogNumber(0);
    edit.SetLogNumber(logfile_number_);
    s = versions_->LogAndApply(&edit, &mutex_);
  }

  if (s.ok()) {

    imm_->Unref();
    imm_ = NULL;
    has_imm_.Release_Store(NULL);
    DeleteObsoleteFiles();
  }

  return s;
}
