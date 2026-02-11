inf_text_remote_delete_operation_recon_feed(GSList* recon_list,
                                            guint position,
                                            InfTextChunk* chunk)
{
  GSList* item;
  InfTextRemoteDeleteOperationRecon* recon;
  GSList* new_list;
  GSList* last;
  InfTextRemoteDeleteOperationRecon* new_recon;

  guint text_pos;
  guint cur_len;
  guint text_len;

  new_list = NULL;
  text_pos = 0;
  cur_len = 0;

  for(item = recon_list; item != NULL; item = g_slist_next(item))
  {
    recon = (InfTextRemoteDeleteOperationRecon*)item->data;
    if(position + text_pos + cur_len < recon->position &&
       text_pos < inf_text_chunk_get_length(chunk))
    {
      text_len = recon->position - position - text_pos - cur_len;
      if(text_len > inf_text_chunk_get_length(chunk) - text_pos)
        text_len = inf_text_chunk_get_length(chunk) - text_pos;

      new_recon = g_slice_new(InfTextRemoteDeleteOperationRecon);
      new_recon->position = position + text_pos + cur_len;
      new_recon->chunk = inf_text_chunk_substring(chunk, text_pos, text_len);
      new_list = g_slist_append_fast(new_list, &last, new_recon);
      text_pos += text_len;
    }

    cur_len += inf_text_chunk_get_length(recon->chunk);
    new_recon = g_slice_new(InfTextRemoteDeleteOperationRecon);
    new_recon->position = recon->position;
    new_recon->chunk = inf_text_chunk_copy(recon->chunk);
    new_list = g_slist_append_fast(new_list, &last, new_recon);
  }

  if(text_pos < inf_text_chunk_get_length(chunk))
  {
    new_recon = g_slice_new(InfTextRemoteDeleteOperationRecon);
    new_recon->position = position + text_pos + cur_len;
    new_recon->chunk = inf_text_chunk_substring(
      chunk,
      text_pos,
      inf_text_chunk_get_length(chunk) - text_pos
    );

    new_list = g_slist_append_fast(new_list, &last, new_recon);
  }

  return new_list;
}
