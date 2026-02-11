operator() (const char* input_p, size_t size) {


  if (g_utf8_validate(input_p, size, 0)) {
    char* out = new char[size + 1];
    std::memcpy(out, input_p, size);
    *(out + size) = 0;
    return SharedHandle<char*>(out);
  }


  SharedHandle<char*> return_val;

  size_t new_size = stored + size;
  char* assembled = join_buffer(input_p, size);

  char* end_p;
  if (g_utf8_validate(assembled, new_size, const_cast<const char**>(&end_p))) {

    return_val = SharedHandle<char*>(assembled);
  }
  else {
    size_t valid_size = end_p - assembled;
    stored = new_size - valid_size;
    if (stored <= buff_size) {
      std::memcpy(buffer, end_p, stored);
      *end_p = 0;
      return_val = SharedHandle<char*>(assembled);
    }
    else {
      stored = 0;
      delete[] assembled;
    }
  }
  return return_val;
}

}
