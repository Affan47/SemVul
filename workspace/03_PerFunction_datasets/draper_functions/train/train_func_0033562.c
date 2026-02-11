read_binary_mask(char *& data, mask_t *& mask)
{
  bool exclude;
  read_binary_number(data, exclude);
  std::string pattern;
  read_binary_string(data, pattern);

  mask = new mask_t(pattern);
  mask->exclude = exclude;
}
