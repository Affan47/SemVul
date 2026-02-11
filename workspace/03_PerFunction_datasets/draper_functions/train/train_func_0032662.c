create(const char *filename)
{
  close();

  if (access(filename, F_OK) == 0)
    return KCT_ERROR_EXIST;


  _f = new fstream(filename, ios::out | ios::binary | ios::trunc);
  if (_f->fail())
    {
      delete _f;
      _f = 0;
      return KCT_ERROR_IO;
    }
  _f->close();


  _f = new fstream(filename, ios::in | ios::out | ios::binary);
  if (_f->fail())
    {
      delete _f;
      _f = 0;
      return KCT_ERROR_IO;
    }

  memset(&_header, 0, sizeof(kct_header_t));
  strcpy(_header.id, "KCemu tape file\032");
  _header.version = KCT_VERSION;

  _f->write((char *)&_header, sizeof(_header));
  if (_f->fail())
    {

      return KCT_ERROR_IO;
    }

  bam_clear(_bam);
  bam_block_allocate(_bam, 0);
  bam_block_allocate(_bam, 1);
  _f->write((char *)&_bam, sizeof(kct_bam_t));
  if (_f->fail())
    {

      return KCT_ERROR_IO;
    }

  return KCT_OK;
}
