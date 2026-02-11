mxf_mpeg_audio_handle_essence_element (const MXFUL * key, GstBuffer * buffer,
    GstCaps * caps, MXFMetadataTimelineTrack * track,
    gpointer mapping_data, GstBuffer ** outbuf)
{
  *outbuf = buffer;


  if (key->u[12] != 0x16 || (key->u[14] != 0x05 && key->u[14] != 0x06
          && key->u[14] != 0x07)) {
    GST_ERROR ("Invalid MPEG audio essence element");
    return GST_FLOW_ERROR;
  }

  return GST_FLOW_OK;
}
