read_line_numbers_from_cod(Processor *cpu)
{
  int j,start_block,end_block,offset;
  int file_id, sline,smod;
  unsigned int address;
  DirBlockInfo *dbi = &main_dir;

  do {
    start_block = get_short_int(&main_dir.dir.block[COD_DIR_LSTTAB]);

    if (start_block) {
      end_block = get_short_int(&main_dir.dir.block[COD_DIR_LSTTAB + 2]);

      int _64k_base = get_short_int(&dbi->dir.block[COD_DIR_HIGHADDR]) << 15;


      for (j = start_block; j <= end_block; j++) {
        read_block(temp_block,j);


        for (offset = 0; offset < (COD_BLOCK_SIZE - COD_LS_SIZE); offset += COD_LS_SIZE) {
          if ((temp_block[offset + COD_LS_SMOD] & 4) == 0) {
            file_id = temp_block[offset + COD_LS_SFILE];
            address = _64k_base + get_short_int(&temp_block[offset + COD_LS_SLOC]);

            sline = get_short_int(&temp_block[offset + COD_LS_SLINE]);
            smod = temp_block[offset + COD_LS_SMOD] & 0xff;

            if ((file_id <= cpu->files.nsrc_files()) &&

                cpu->IsAddressInRange(address) &&
                (smod == 0x80))
              cpu->attach_src_line(address, file_id, sline, 0);
          }
        }
      }
      cpu->read_src_files();
    }

    dbi = dbi->next_dir_block_info;
   } while (dbi);
}
