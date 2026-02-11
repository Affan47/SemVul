StartProfiling(const char* title, unsigned uid) {
  ASSERT(uid > 0);
  current_profiles_semaphore_->Wait();
  if (current_profiles_.length() >= kMaxSimultaneousProfiles) {
    current_profiles_semaphore_->Signal();
    return false;
  }
  for (int i = 0; i < current_profiles_.length(); ++i) {
    if (strcmp(current_profiles_[i]->title(), title) == 0) {

      current_profiles_semaphore_->Signal();
      return false;
    }
  }
  current_profiles_.Add(new CpuProfile(title, uid));
  current_profiles_semaphore_->Signal();
  return true;
}
