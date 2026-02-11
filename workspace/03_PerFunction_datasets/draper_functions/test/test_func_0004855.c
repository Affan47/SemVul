dvb_base_bin_handle_message (GstBin * bin, GstMessage * message)
{
  DvbBaseBin *dvbbasebin;

  dvbbasebin = GST_DVB_BASE_BIN (bin);

  if (message->type == GST_MESSAGE_ELEMENT &&
      GST_ELEMENT (message->src) == GST_ELEMENT (dvbbasebin->mpegtsparse)) {
    const gchar *structure_name = gst_structure_get_name (message->structure);

    if (strcmp (structure_name, "pat") == 0)
      dvb_base_bin_pat_info_cb (dvbbasebin, message->structure);
    else if (strcmp (structure_name, "pmt") == 0)
      dvb_base_bin_pmt_info_cb (dvbbasebin, message->structure);


    gst_element_post_message (GST_ELEMENT_CAST (bin), message);
  } else {

    GST_BIN_CLASS (parent_class)->handle_message (bin, message);
  }

}
