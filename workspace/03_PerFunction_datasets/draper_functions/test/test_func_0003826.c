cmCPackTarCompress_Data_Close(void *client_data)
{
  cmCPackTarCompress_Data *mydata = (cmCPackTarCompress_Data*)client_data;

  if ( !cmcompress_compress_finalize(&mydata->CMCompressStream) )
    {
    delete mydata->OutputStream;
    return -1;
    }

  delete mydata->OutputStream;
  mydata->OutputStream = 0;
  return (0);
}
