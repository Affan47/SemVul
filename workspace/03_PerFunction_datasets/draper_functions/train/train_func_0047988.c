_my_calc_total_blob_length(MI_INFO *info, const uchar *record)
{
  ulong length;
  MI_BLOB *blob,*end;

  for (length=0, blob= info->blobs, end=blob+info->s->base.blobs ;
       blob != end;
       blob++)
  {
    blob->length=_mi_calc_blob_length(blob->pack_length,record + blob->offset);
    length+=blob->length;
  }
  return length;
}
