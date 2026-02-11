add_handlers()
{
  add_read_handler("p_bit_error", random_bit_errors_read, (void *)0);
  add_write_handler("p_bit_error", reconfigure_keyword_handler, "0 P");
  add_read_handler("error_kind", random_bit_errors_read, (void *)1);
  add_write_handler("error_kind", reconfigure_keyword_handler, "1 KIND");
  add_data_handlers("active", Handler::OP_READ | Handler::OP_WRITE, &_on);
}
