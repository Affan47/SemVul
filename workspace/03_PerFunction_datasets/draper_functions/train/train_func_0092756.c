StopGetAllPorts() {
  ASSERT(talk_base::Thread::Current() == network_thread_);
  running_ = false;
  network_thread_->Clear(this, MSG_ALLOCATE);
  for (uint32 i = 0; i < sequences_.size(); ++i)
    sequences_[i]->Stop();
}
