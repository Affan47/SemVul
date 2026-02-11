send_delta_native(
  Xfer *pXfer,
  int rid,
  int isPrivate,
  Blob *pUuid
){
  Blob src, delta;
  int size = 0;
  int srcId;

  srcId = db_int(0, "SELECT srcid FROM delta WHERE rid=%d", rid);
  if( srcId>0
   && (pXfer->syncPrivate || !content_is_private(srcId))
  ){
    blob_zero(&src);
    db_blob(&src, "SELECT uuid FROM blob WHERE rid=%d", srcId);
    if( uuid_is_shunned(blob_str(&src)) ){
      blob_reset(&src);
      return 0;
    }
    blob_zero(&delta);
    db_blob(&delta, "SELECT content FROM blob WHERE rid=%d", rid);
    blob_uncompress(&delta, &delta);
    if( isPrivate ) blob_append(pXfer->pOut, "private\n", -1);
    blob_appendf(pXfer->pOut, "file %b %b %d\n",
                pUuid, &src, blob_size(&delta));
    blob_append(pXfer->pOut, blob_buffer(&delta), blob_size(&delta));
    size = blob_size(&delta);
    blob_reset(&delta);
    blob_reset(&src);
  }else{
    size = 0;
  }
  return size;
}
