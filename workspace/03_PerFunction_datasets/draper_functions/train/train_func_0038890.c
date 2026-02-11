append_to_current_block (MPEGPacketiser * p, guint64 offset, guint8 pack_type)
{
  MPEGBlockInfo *block;

  if (G_UNLIKELY (p->cur_block_idx == -1))
    return;


  g_assert (p->blocks != NULL && p->cur_block_idx < p->n_blocks);
  block = p->blocks + p->cur_block_idx;


  g_assert (block->offset < offset);
  block->length = offset - block->offset;


  switch (pack_type) {
    case MPEG_PACKET_SEQUENCE:
      g_assert (!(block->flags &
              (MPEG_BLOCK_FLAG_GOP | MPEG_BLOCK_FLAG_PICTURE)));
      block->flags |= MPEG_BLOCK_FLAG_SEQUENCE;
      break;
    case MPEG_PACKET_GOP:
      block->flags |= MPEG_BLOCK_FLAG_GOP;
      break;
    case MPEG_PACKET_PICTURE:
      block->flags |= MPEG_BLOCK_FLAG_PICTURE;
      break;
    default:
      break;
  }
}
