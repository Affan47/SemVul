unregister_io_write_handler(void *this_ptr, bx_write_handler_t f,
                                          Bit32u addr, Bit8u mask)
{
  addr &= 0xffff;

  struct io_handler_struct *io_write_handler = write_port_to_handler[addr];

  if (!io_write_handler)
    return 0;

  if (io_write_handler == &io_write_handlers)
    return 0;

  if (io_write_handler->funct != f)
    return 0;

  if (io_write_handler->this_ptr != this_ptr)
    return 0;

  if (io_write_handler->mask != mask)
    return 0;

  write_port_to_handler[addr] = &io_write_handlers;
  io_write_handler->usage_count--;

  if (!io_write_handler->usage_count) {
    io_write_handler->prev->next = io_write_handler->next;
    io_write_handler->next->prev = io_write_handler->prev;
    delete [] io_write_handler->handler_name;
    delete io_write_handler;
  }
  return 1;
}
