gridfile_read_from_pending_buffer(gridfile *gfile, gridfs_offset totalBytesToRead, char* buf,
                                                       int *first_chunk){
  gridfs_offset realSize = 0;
  if( gfile->pending_len > 0 && *first_chunk == gfile->chunk_num) {
    char *chunk_data;
    gridfs_offset chunksize = gridfile_get_chunksize(gfile);
    gridfs_offset ofs = gfile->pos - gfile->chunk_num * chunksize;
    realSize = MIN( totalBytesToRead, gfile->pending_len - ofs );
    chunk_data = gfile->pending_data + ofs;
    memcpy( buf, chunk_data, (size_t)realSize );
    (*first_chunk)++;
  };
  return realSize;
}
