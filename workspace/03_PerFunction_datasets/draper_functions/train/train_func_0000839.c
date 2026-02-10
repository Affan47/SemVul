data_write_file( disk_t *d, FILE *file, int seclen )
{
  int len = 0x80 << seclen;
  if( fwrite( &d->track[ d->i ], len, 1, file ) != 1 )
    return 1;
  return 0;
}
