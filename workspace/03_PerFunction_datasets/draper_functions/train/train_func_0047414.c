finish_codec_negotiation (
    GList *old_codec_associations,
    GList *new_codec_associations)
{
  int i;
  GList *item;


  for (i=0; i < 128; i++)
  {
    CodecAssociation *local_ca = NULL;


    if (lookup_codec_association_by_pt_list (new_codec_associations, i, TRUE))
      continue;


    local_ca = lookup_codec_association_by_pt_list (old_codec_associations,
        i, FALSE);
    if (local_ca) {
      CodecAssociation *new_ca = codec_association_copy (local_ca);
      new_ca->recv_only = TRUE;
      new_codec_associations = g_list_append (new_codec_associations, new_ca);
    }
  }

  for (item = new_codec_associations; item; item = g_list_next (item))
  {
    CodecAssociation *new_ca = item->data;
    CodecAssociation *old_ca = NULL;

    if (new_ca->disable || new_ca->reserved || new_ca->recv_only)
    {
      new_ca->need_config = FALSE;
      continue;
    }

    old_ca = lookup_codec_association_custom_internal (old_codec_associations,
        TRUE, match_send_codec_no_pt, new_ca);
    if (old_ca)
      keep_config_from_old_codec (new_ca->codec, old_ca->codec);

    new_ca->need_config = codec_needs_config (new_ca->codec);
  }

  return new_codec_associations;
}
