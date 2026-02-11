write_cod_block(DirBlockInfo *dbp,
                int block_ptr_start,
                int block_ptr_end,
                Block *bptr)
{


  if(!gp_getl16(&dbp->dir.block[block_ptr_start]))
    gp_putl16(&dbp->dir.block[block_ptr_start], bptr->block_number);

  gp_putl16(&dbp->dir.block[block_ptr_end], bptr->block_number);

  fseek(state.cod.f, COD_BLOCK_SIZE*bptr->block_number, SEEK_SET);
  fwrite(bptr->block, 1, COD_BLOCK_SIZE, state.cod.f);

}
