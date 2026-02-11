Inflate(int flush) {
  if ((zerror_ == Z_OK) && (zcontext_.avail_out == 0)) {

  } else if (zcontext_.avail_in == 0) {
    const void* in;
    int in_size;
    bool first = zcontext_.next_in == NULL;
    bool ok = sub_stream_->Next(&in, &in_size);
    if (!ok) {
      zcontext_.next_out = NULL;
      zcontext_.avail_out = 0;
      return Z_STREAM_END;
    }
    zcontext_.next_in = static_cast<Bytef*>(const_cast<void*>(in));
    zcontext_.avail_in = in_size;
    if (first) {
      int error = internalInflateInit2(&zcontext_, format_);
      if (error != Z_OK) {
        return error;
      }
    }
  }
  zcontext_.next_out = static_cast<Bytef*>(output_buffer_);
  zcontext_.avail_out = output_buffer_length_;
  output_position_ = output_buffer_;
  int error = inflate(&zcontext_, flush);
  return error;
}
