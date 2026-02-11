ErrorName(int err, const ConstantLabel * err_table) {
  if (err == 0)
    return "No error";

  if (err_table != 0) {
    if (const char * value = FindLabel(err, err_table))
      return value;
  }

  char buffer[16];
  snprintf(buffer, sizeof(buffer), "0x%08x", err);
  return buffer;
}
