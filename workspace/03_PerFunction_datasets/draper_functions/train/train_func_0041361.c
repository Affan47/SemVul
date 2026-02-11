upd_fdc_master_reset( upd_fdc *f )
{
  int i;
  for( i = 0; i < 4; i++ )
    if( f->drive[i] != NULL )
      fdd_select( &f->drive[i]->fdd, i == 0 ? 1 : 0 );
  f->current_drive = f->drive[0];

  f->main_status = UPD_FDC_MAIN_DATAREQ;
  for( i = 0; i < 4; i++ )
    f->status_register[i] = f->pcn[i] = f->seek[i] = 0;
  f->stp_rate = 16;
  f->hut_time = 240;
  f->hld_time = 254;
  f->non_dma = 1;
  f->direction = 0;
  f->head_load = 0;
  f->intrq = UPD_INTRQ_NONE;
  f->state = UPD_FDC_STATE_CMD;
  f->cycle = 0;
  f->last_sector_read = 0;
  f->read_id = 0;

  if( f->speedlock != -1 ) f->speedlock = 0;
}
