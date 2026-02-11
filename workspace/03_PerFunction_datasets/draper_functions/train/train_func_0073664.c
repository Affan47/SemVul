llrpc(unsigned command, void *data)
{
  if (command == CLICK_LLRPC_PROXY) {
    click_llrpc_proxy_st* proxy = static_cast<click_llrpc_proxy_st*>(data);
    const Handler* h = static_cast<Handler*>(proxy->proxied_handler);

    String fn = handler_name_to_file_name(h->name());
    int fd = open(fn.c_str(), O_RDONLY);
    int err = errno;

    if (fd < 0) {
      if (_verbose)
	complain_about_open(ErrorHandler::default_handler(), h->name(), err);

      return complain_about_open(0, h->name(), err);
    }

    click_chatter("about to %x on %s", proxy->proxied_command, fn.c_str());
    int retval = ioctl(fd, proxy->proxied_command, proxy->proxied_data);
    err = errno;

    close(fd);
    return (retval >= 0 ? retval : -err);

  } else
    return Element::llrpc(command, data);
}
