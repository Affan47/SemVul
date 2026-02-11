Finish() {
#ifdef DEBUG
  ASSERT(state_ == SWEEP_SPACES || state_ == RELOCATE_OBJECTS);
  state_ = IDLE;
#endif


  heap()->isolate()->stub_cache()->Clear();

  heap()->external_string_table_.CleanUp();


  if (HasCompacted()) return;


  static const int kFragmentationLimit = 15;
  static const int kFragmentationAllowed = 1 * MB;
  intptr_t old_gen_recoverable = 0;
  intptr_t old_gen_used = 0;

  OldSpaces spaces;
  for (OldSpace* space = spaces.next(); space != NULL; space = spaces.next()) {
    old_gen_recoverable += space->Waste() + space->AvailableFree();
    old_gen_used += space->Size();
  }

  int old_gen_fragmentation =
      static_cast<int>((old_gen_recoverable * 100.0) / old_gen_used);
  if (old_gen_fragmentation > kFragmentationLimit &&
      old_gen_recoverable > kFragmentationAllowed) {
    compact_on_next_gc_ = true;
  }
}
