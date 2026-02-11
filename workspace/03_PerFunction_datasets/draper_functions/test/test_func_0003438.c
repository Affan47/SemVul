dvb_base_bin_reset (DvbBaseBin * dvbbasebin)
{
  if (dvbbasebin->hwcam) {
    cam_device_close (dvbbasebin->hwcam);
    cam_device_free (dvbbasebin->hwcam);
    dvbbasebin->hwcam = NULL;
  }

  if (dvbbasebin->ts_pad) {
    gst_element_release_request_pad (GST_ELEMENT (dvbbasebin->mpegtsparse),
        dvbbasebin->ts_pad);
    dvbbasebin->ts_pad = NULL;
  }
}
