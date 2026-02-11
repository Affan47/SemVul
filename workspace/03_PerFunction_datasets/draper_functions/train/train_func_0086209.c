AddCurrentStack() {
  TickSampleEventRecord record;
  TickSample* sample = &record.sample;
  sample->state = Top::current_vm_state();
  sample->pc = reinterpret_cast<Address>(sample);
  sample->tos = NULL;
  sample->frames_count = 0;
  for (StackTraceFrameIterator it;
       !it.done() && sample->frames_count < TickSample::kMaxFramesCount;
       it.Advance()) {
    sample->stack[sample->frames_count++] = it.frame()->pc();
  }
  record.order = enqueue_order_;
  ticks_from_vm_buffer_.Enqueue(record);
}
