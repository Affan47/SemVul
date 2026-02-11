client_option_bitwise_secfile_str(secfile_data_t data,
                                                     int val)
{
  const struct strvec *names = CLIENT_OPTION(data)->bitwise.support_names;

  return (0 <= val && val < strvec_size(names)
          ? strvec_get(names, val) : NULL);
}
