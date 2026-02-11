exit()
{

  struct io_handler_struct *io_read_handler = io_read_handlers.next;
  struct io_handler_struct *curr = NULL;
  while (io_read_handler != &io_read_handlers) {
    io_read_handler->prev->next = io_read_handler->next;
    io_read_handler->next->prev = io_read_handler->prev;
    curr = io_read_handler;
    io_read_handler = io_read_handler->next;
    delete [] curr->handler_name;
    delete curr;
  }
  struct io_handler_struct *io_write_handler = io_write_handlers.next;
  while (io_write_handler != &io_write_handlers) {
    io_write_handler->prev->next = io_write_handler->next;
    io_write_handler->next->prev = io_write_handler->prev;
    curr = io_write_handler;
    io_write_handler = io_write_handler->next;
    delete [] curr->handler_name;
    delete curr;
  }

  bx_virt_timer.setup();
  bx_slowdown_timer.exit();

  PLUG_unload_plugin(pit);
  PLUG_unload_plugin(cmos);
  PLUG_unload_plugin(dma);
  PLUG_unload_plugin(pic);
  PLUG_unload_plugin(vga);
  PLUG_unload_plugin(floppy);
#if BX_SUPPORT_PCI
  PLUG_unload_plugin(pci);
  PLUG_unload_plugin(pci2isa);
#endif
  bx_unload_plugins();
  init_stubs();
}
