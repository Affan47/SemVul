mpegts_base_handle_psi (MpegTSBase * base, GstMpegTsSection * section)
{
  gboolean post_message = TRUE;

  GST_DEBUG ("Handling PSI (pid: 0x%04x , table_id: 0x%02x)",
      section->pid, section->table_id);

  switch (section->section_type) {
    case GST_MPEGTS_SECTION_PAT:
      post_message = mpegts_base_apply_pat (base, section);
      if (base->seen_pat == FALSE) {
        base->seen_pat = TRUE;
        GST_DEBUG ("First PAT offset: %" G_GUINT64_FORMAT, section->offset);
        mpegts_packetizer_set_reference_offset (base->packetizer,
            section->offset);
      }
      break;
    case GST_MPEGTS_SECTION_PMT:
      post_message = mpegts_base_apply_pmt (base, section);
      break;
    case GST_MPEGTS_SECTION_EIT:

      post_message = mpegts_base_get_tags_from_eit (base, section);
      break;
    default:
      break;
  }


  if (post_message)
    gst_element_post_message (GST_ELEMENT_CAST (base),
        gst_message_new_mpegts_section (GST_OBJECT (base), section));
  gst_mpegts_section_unref (section);
}
