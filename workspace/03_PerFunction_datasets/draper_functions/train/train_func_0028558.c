init_paging() {
  end_mem = multiboot_ptr->mem_upper * 1024;

  frames = (unsigned int*) kmalloc(end_mem / 0x1000, 0);
  memset(frames, 0, end_mem / 0x1000 / 8);

  num_frames = end_mem / 0x1000;
  frames = (unsigned*)kmalloc(INDEX_FROM_BIT(num_frames), 0);
  memset(frames, 0, INDEX_FROM_BIT(num_frames));


  kernel_directory = (page_directory_t*)kmalloc(sizeof(page_directory_t), 1);
  memset(kernel_directory, 0, sizeof(page_directory_t));
  current_directory = kernel_directory;

  unsigned int i = 0;
  while (i < (unsigned int)&_kernel_end) {

    alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
    i += 0x1000;
  }


  install_isr(14, page_fault);


  __asm__ volatile("mov %0, %%cr3":: "r"(&kernel_directory->tables_phys));
  uint32_t cr0;
  __asm__ volatile("mov %%cr0, %0": "=r"(cr0));
  cr0 |= 0x80000000;
  __asm__ volatile("mov %0, %%cr0":: "r"(cr0));
}
