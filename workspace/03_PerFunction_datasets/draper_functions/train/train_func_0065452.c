gap_file_load_file_segment(const char *filename
                  ,guchar *segment_data_ptr
                  ,gint32 seek_index
                  ,gint32 segment_size
                  )
{
  FILE *fp;
  gint32      l_bytes_read;


  l_bytes_read = 0;

  fp = g_fopen(filename, "rb");
  if (fp)
  {

    fseek(fp, seek_index, SEEK_SET);


    l_bytes_read = fread(segment_data_ptr, 1, (size_t)segment_size, fp);

    fclose(fp);
  }

  if(gap_debug) printf("gap_file_load_file_segment: %s seek_idx:%d  bytes_read:%d\n", filename, (int)seek_index, (int)l_bytes_read);

  return(l_bytes_read);

}
