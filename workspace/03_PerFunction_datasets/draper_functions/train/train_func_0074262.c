WebPSetWorkerInterface(const WebPWorkerInterface* const winterface) {
  if (winterface == NULL ||
      winterface->Init == NULL || winterface->Reset == NULL ||
      winterface->Sync == NULL || winterface->Launch == NULL ||
      winterface->Execute == NULL || winterface->End == NULL) {
    return 0;
  }
  g_worker_interface = *winterface;
  return 1;
}
