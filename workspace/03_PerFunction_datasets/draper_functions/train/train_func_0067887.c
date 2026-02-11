addr_to_string (ACEXML_Char *s,
                                 size_t size,
                                 int ipaddr_format) const
{
  size_t total_len = this->calculate_length (ipaddr_format);
  if (size < total_len)
    return -1;
  else
    {
      ACE_OS::sprintf (s, ACE_TEXT ("%s:%d/%s"),
                       ACE_TEXT_CHAR_TO_TCHAR (ipaddr_format == 0
                                               ? this->get_host_name ()
                                               : this->get_host_addr ()),
                       this->get_port_number (),
                       this->get_path_name ());
      return 0;
    }
}
