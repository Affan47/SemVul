gst_rdt_manager_parse_caps (GstRDTManager * rdtmanager,
    GstRDTManagerSession * session, GstCaps * caps)
{
  GstStructure *caps_struct;
  guint val;


  caps_struct = gst_caps_get_structure (caps, 0);

  GST_DEBUG_OBJECT (rdtmanager, "got caps");


  if (!gst_structure_get_int (caps_struct, "clock-rate", &session->clock_rate))
    session->clock_rate = 1000;

  if (session->clock_rate <= 0)
    goto wrong_rate;

  GST_DEBUG_OBJECT (rdtmanager, "got clock-rate %d", session->clock_rate);


  if (gst_structure_get_uint (caps_struct, "clock-base", &val))
    session->clock_base = val;
  else
    session->clock_base = -1;

  GST_DEBUG_OBJECT (rdtmanager, "got clock-base %" G_GINT64_FORMAT,
      session->clock_base);


  if (gst_structure_get_uint (caps_struct, "seqnum-base", &val))
    session->next_seqnum = val;
  else
    session->next_seqnum = -1;

  GST_DEBUG_OBJECT (rdtmanager, "got seqnum-base %d", session->next_seqnum);

  return TRUE;


wrong_rate:
  {
    GST_DEBUG_OBJECT (rdtmanager, "Invalid clock-rate %d", session->clock_rate);
    return FALSE;
  }
}
