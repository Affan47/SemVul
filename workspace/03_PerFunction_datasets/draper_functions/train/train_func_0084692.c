GetLogLines(int from_pos, char* dest_buf, int max_size) {
  if (Write != WriteToMemory) return 0;
  ASSERT(output_buffer_ != NULL);
  ASSERT(from_pos >= 0);
  ASSERT(max_size >= 0);
  int actual_size = output_buffer_->Read(from_pos, dest_buf, max_size);
  ASSERT(actual_size <= max_size);
  if (actual_size == 0) return 0;


  char* end_pos = dest_buf + actual_size - 1;
  while (end_pos >= dest_buf && *end_pos != '\n') --end_pos;
  actual_size = static_cast<int>(end_pos - dest_buf + 1);


  ASSERT(actual_size > 0);
  ASSERT(actual_size <= max_size);
  return actual_size;
}
