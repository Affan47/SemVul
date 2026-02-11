LowLevelCodeCreateEvent(Code* code,
                                     const char* name,
                                     int name_size) {
  if (log_->ll_output_handle_ == NULL) return;
  LowLevelCodeCreateStruct event;
  event.name_size = name_size;
  event.code_address = code->instruction_start();
  ASSERT(event.code_address == code->address() + Code::kHeaderSize);
  event.code_size = code->instruction_size();
  LowLevelLogWriteStruct(event);
  LowLevelLogWriteBytes(name, name_size);
  LowLevelLogWriteBytes(
      reinterpret_cast<const char*>(code->instruction_start()),
      code->instruction_size());
}
