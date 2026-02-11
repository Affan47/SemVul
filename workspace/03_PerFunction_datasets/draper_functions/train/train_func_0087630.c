_dbx_init(dbx_t *dbx)
{
  unsigned int signature[4];

  dbx->message_count = 0;
  dbx->capacity = 0;
  dbx->info = NULL;

  fseek(dbx->file, 0L, SEEK_END);
  dbx->file_size = ftell(dbx->file);
  fseek(dbx->file, 0L, SEEK_SET);

  fread(signature, 4, 4, dbx->file);

  if (signature[0] == 0xFE12ADCF &&
      signature[1] == 0x6F74FDC5 &&
      signature[2] == 0x11D1E366 &&
      signature[3] == 0xC0004E9A) {
    dbx->type = DBX_TYPE_EMAIL;
  }
  else if (signature[0] == 0x36464D4A &&
	   signature[1] == 0x00010003) {
    dbx->type = DBX_TYPE_OE4;
  }
  else if (signature[0]==0xFE12ADCF &&
	   signature[1]==0x6F74FDC6 &&
	   signature[2]==0x11D1E366 &&
	   signature[3]==0xC0004E9A) {
    dbx->type = DBX_TYPE_FOLDER;
  }
  else {
    dbx->type = DBX_TYPE_UNKNOWN;
  }

  if (dbx->type == DBX_TYPE_EMAIL) {
    _dbx_read_indexes(dbx);
    _dbx_read_info(dbx);
    qsort(dbx->info, dbx->message_count, sizeof(dbx_info_t), (dbx_cmpfunc_t) _dbx_info_cmp);
    _dbx_uniquify_filenames(dbx);
  }
}
