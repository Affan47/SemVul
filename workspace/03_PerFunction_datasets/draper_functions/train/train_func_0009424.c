_mi_mempack_get_block_info(MI_INFO *myisam, MI_BIT_BUFF *bit_buff,
                                         MI_BLOCK_INFO *info, uchar **rec_buff_p,
					 uchar *header)
{
  header+= read_pack_length((uint) myisam->s->pack.version, header,
                            &info->rec_len);
  if (myisam->s->base.blobs)
  {
    header+= read_pack_length((uint) myisam->s->pack.version, header,
                              &info->blob_len);

    if (!(mi_alloc_rec_buff(myisam, info->blob_len,
			    rec_buff_p)))
      return 0;
    bit_buff->blob_pos= (uchar*) *rec_buff_p;
    bit_buff->blob_end= (uchar*) *rec_buff_p + info->blob_len;
  }
  return header;
}
