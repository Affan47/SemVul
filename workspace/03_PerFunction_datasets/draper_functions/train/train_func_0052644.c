register_io_read_handler(void *this_ptr, bx_read_handler_t f,
                                               Bit32u addr, const char *name, Bit8u mask)
{
  addr &= 0xffff;

  if (!f)
    return 0;


  if (read_port_to_handler[addr] &&
      read_port_to_handler[addr] != &io_read_handlers) {
    BX_ERROR(("IO device address conflict(read) at IO address %Xh",
              (unsigned) addr));
    BX_ERROR(("  conflicting devices: %s & %s",
              read_port_to_handler[addr]->handler_name, name));
    return 0;
  }


  struct io_handler_struct *curr = &io_read_handlers;
  struct io_handler_struct *io_read_handler = NULL;
  do {
    if (curr->funct == f &&
        curr->mask == mask &&
        curr->this_ptr == this_ptr &&
        !strcmp(curr->handler_name, name)) {
      io_read_handler = curr;
      break;
    }
    curr = curr->next;
  } while (curr->next != &io_read_handlers);

  if (!io_read_handler) {
    io_read_handler = new struct io_handler_struct;
    io_read_handler->funct = (void *)f;
    io_read_handler->this_ptr = this_ptr;
    io_read_handler->handler_name = new char[strlen(name)+1];
    strcpy(io_read_handler->handler_name, name);
    io_read_handler->mask = mask;
    io_read_handler->usage_count = 0;

    io_read_handlers.prev->next = io_read_handler;
    io_read_handler->next = &io_read_handlers;
    io_read_handler->prev = io_read_handlers.prev;
    io_read_handlers.prev = io_read_handler;
  }

  io_read_handler->usage_count++;
  read_port_to_handler[addr] = io_read_handler;
  return 1;
}
