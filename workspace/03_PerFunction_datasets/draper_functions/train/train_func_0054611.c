_dbx_read_index(dbx_t *dbx, long pos)
{
  int i;
  long next_table;
  char ptr_count = 0;
  long index_count;

  if (pos < 0 || pos >= dbx->file_size) {
    return 0;
  }

  fseek(dbx->file, pos + 8L, SEEK_SET);
  fread(&next_table, 4, 1, dbx->file);
  fseek(dbx->file, 5L, SEEK_CUR);
  fread(&ptr_count, 1, 1, dbx->file);
  fseek(dbx->file, 2L, SEEK_CUR);
  fread(&index_count, 4, 1, dbx->file);

  if (index_count > 0) {
    if (!_dbx_read_index(dbx, next_table))
      return 0;
  }

  pos += 24;

  dbx->info = (dbx_info_t *)realloc(dbx->info, (dbx->capacity + ptr_count) * sizeof(dbx_info_t));
  dbx->capacity += ptr_count;
  for (i = 0; i < ptr_count; i++) {
    int index_ptr;
    fseek(dbx->file, pos, SEEK_SET);
    fread(&index_ptr, 4, 1, dbx->file);
    fread(&next_table, 4, 1, dbx->file);
    fread(&index_count, 4, 1, dbx->file);

    memset(dbx->info + dbx->message_count, 0, sizeof(dbx_info_t));
    dbx->info[dbx->message_count].index = index_ptr;
    dbx->message_count++;

    pos += 12;
    if (index_count > 0) {
      if (!_dbx_read_index(dbx, next_table))
	return 0;
    }
  }

  return 1;
}
