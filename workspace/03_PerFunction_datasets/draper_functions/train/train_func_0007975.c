NewArena(int32 flags,
                                              Arena *meta_data_arena) {
  RAW_CHECK(meta_data_arena != 0, "must pass a valid arena");
  if (meta_data_arena == &default_arena) {
    if ((flags & LowLevelAlloc::kAsyncSignalSafe) != 0) {
      meta_data_arena = &unhooked_async_sig_safe_arena;
    } else if ((flags & LowLevelAlloc::kCallMallocHook) == 0) {
      meta_data_arena = &unhooked_arena;
    }
  }

  Arena *result =
    new (AllocWithArena(sizeof (*result), meta_data_arena)) Arena(0);
  ArenaInit(result);
  result->flags = flags;
  return result;
}
