write_directory(void)
{
  DirBlockInfo *dbi;
  dbi = &main_dir;

  do {
    fseek(state.cod.f,COD_BLOCK_SIZE * dbi->dir.block_number, SEEK_SET);
    fwrite(dbi->dir.block, 1, COD_BLOCK_SIZE, state.cod.f);

    dbi = dbi->next_dir_block_info;
  } while(dbi);
}
