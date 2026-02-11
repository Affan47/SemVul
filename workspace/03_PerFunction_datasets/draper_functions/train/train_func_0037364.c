DeleteDebuggerInspectableFrame(DeoptimizedFrameInfo* info,
                                                 Isolate* isolate) {
  ASSERT(isolate == Isolate::Current());
  ASSERT(isolate->deoptimizer_data()->deoptimized_frame_info_ == info);
  delete info;
  isolate->deoptimizer_data()->deoptimized_frame_info_ = NULL;
}
