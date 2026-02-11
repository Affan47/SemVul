_init_local (void)
{
  GST_DEBUG_CATEGORY_INIT (mpegts_packetizer_debug, "mpegtspacketizer", 0,
      "MPEG transport stream parser");

  QUARK_PAT = g_quark_from_string ("pat");
  QUARK_TRANSPORT_STREAM_ID = g_quark_from_string ("transport-stream-id");
  QUARK_PROGRAM_NUMBER = g_quark_from_string ("program-number");
  QUARK_PID = g_quark_from_string ("pid");
  QUARK_PROGRAMS = g_quark_from_string ("programs");

  QUARK_PMT = g_quark_from_string ("pmt");
  QUARK_PCR_PID = g_quark_from_string ("pcr-pid");
  QUARK_VERSION_NUMBER = g_quark_from_string ("version-number");
  QUARK_DESCRIPTORS = g_quark_from_string ("descriptors");
  QUARK_STREAM_TYPE = g_quark_from_string ("stream-type");
  QUARK_STREAMS = g_quark_from_string ("streams");

  QUARK_NIT = g_quark_from_string ("nit");
  QUARK_NETWORK_ID = g_quark_from_string ("network-id");
  QUARK_CURRENT_NEXT_INDICATOR = g_quark_from_string ("current-next-indicator");
  QUARK_ACTUAL_NETWORK = g_quark_from_string ("actual-network");
  QUARK_NETWORK_NAME = g_quark_from_string ("network-name");
  QUARK_ORIGINAL_NETWORK_ID = g_quark_from_string ("original-network-id");
  QUARK_TRANSPORTS = g_quark_from_string ("transports");

  QUARK_SDT = g_quark_from_string ("sdt");
  QUARK_ACTUAL_TRANSPORT_STREAM =
      g_quark_from_string ("actual-transport-stream");
  QUARK_SERVICES = g_quark_from_string ("services");

  QUARK_EIT = g_quark_from_string ("eit");
  QUARK_SERVICE_ID = g_quark_from_string ("service-id");
  QUARK_PRESENT_FOLLOWING = g_quark_from_string ("present-following");
  QUARK_SEGMENT_LAST_SECTION_NUMBER =
      g_quark_from_string ("segment-last-section-number");
  QUARK_LAST_TABLE_ID = g_quark_from_string ("last-table-id");
  QUARK_EVENTS = g_quark_from_string ("events");
}
