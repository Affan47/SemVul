avi_write_ix(AVFormatContext *s)
{
    ByteIOContext *pb = s->pb;
    AVIContext *avi = s->priv_data;
    char tag[5];
    char ix_tag[] = "ix00";
    int i, j;

    assert(!url_is_streamed(pb));

    if (avi->riff_id > AVI_MASTER_INDEX_SIZE)
        return -1;

    for (i=0;i<s->nb_streams;i++) {
         int64_t ix, pos;

         avi_stream2fourcc(&tag[0], i, s->streams[i]->codec->codec_type);
         ix_tag[3] = '0' + i;


         ix = url_ftell(pb);
         put_tag(pb, &ix_tag[0]);
         put_le32(pb, avi->indexes[i].entry * 8 + 24);

         put_le16(pb, 2);
         put_byte(pb, 0);
         put_byte(pb, 1);
         put_le32(pb, avi->indexes[i].entry);

         put_tag(pb, &tag[0]);
         put_le64(pb, avi->movi_list);
         put_le32(pb, 0);

         for (j=0; j<avi->indexes[i].entry; j++) {
             AVIIentry* ie = avi_get_ientry(&avi->indexes[i], j);
             put_le32(pb, ie->pos + 8);
             put_le32(pb, ((uint32_t)ie->len & ~0x80000000) |
                          (ie->flags & 0x10 ? 0 : 0x80000000));
         }
         put_flush_packet(pb);
         pos = url_ftell(pb);


         url_fseek(pb, avi->indexes[i].indx_start - 8, SEEK_SET);
         put_tag(pb, "indx");
         url_fskip(pb, 8);
         put_le32(pb, avi->riff_id);
         url_fskip(pb, 16*avi->riff_id);
         put_le64(pb, ix);
         put_le32(pb, pos - ix);
         put_le32(pb, avi->indexes[i].entry);

         url_fseek(pb, pos, SEEK_SET);
    }
    return 0;
}
