cod_write_code(void)
{
  MemBlock *m = state.i_memory;
  int mem_base;

  int i,offset;
  int start_address = 0, used_flag = 0;
  DirBlockInfo *dbi;
  Block rb = {NULL, 0};

  offset = 0;

  while(m) {
    mem_base = m->base << I_MEM_BITS;

    for(i=mem_base; (i-mem_base) <= MAX_I_MEM; i++) {
      if ((i_memory_get(state.i_memory, i) & MEM_USED_MASK) &&
          ((i-mem_base) < MAX_I_MEM)) {
	cod_emit_opcode(i, i_memory_get(state.i_memory, i) & 0xffff);
	if(used_flag == 0) {

          start_address = i;
	  used_flag = 1;
	  if(rb.block == NULL) {
	    gp_cod_create(&rb, &blocks);
	  }
	}
      }
      else {


	if(used_flag == 1) {


	  gp_putl16(&rb.block[offset], 2*start_address);
	  gp_putl16(&rb.block[offset+2], 2*(i-1) + 1);

	  offset += 4;
	  if(offset>=COD_BLOCK_SIZE) {


	    write_cod_range_block(start_address, &rb);
	    gp_cod_delete(&rb);
	    offset = 0;
	  }
	  used_flag = 0;
	}
      }
    }

    if(offset) {
      write_cod_range_block(start_address, &rb);
      gp_cod_delete(&rb);
      offset = 0;
      used_flag = 0;
    }

    m = m->next;
  }


  dbi = &main_dir;
  do {
    for(i=0; i<COD_CODE_IMAGE_BLOCKS; i++)
      if(dbi->cod_image_blocks[i].block) {
	write_cod_block(dbi,
                        COD_DIR_CODE+i*2,
                        COD_DIR_CODE+i*2,
                        &dbi->cod_image_blocks[i]);
	free(dbi->cod_image_blocks[i].block);
      }
    dbi = dbi->next_dir_block_info;
  } while(dbi);

}
