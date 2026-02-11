destroy_pad (PadInfos * infos)
{
  if (G_LIKELY (infos->bin)) {
    gst_element_set_state (infos->bin, GST_STATE_NULL);
    gst_element_unlink (infos->bin, infos->self->adder);
    gst_bin_remove (GST_BIN (infos->self), infos->bin);
  }

  if (infos->adder_pad) {
    gst_element_release_request_pad (infos->self->adder, infos->adder_pad);
    gst_object_unref (infos->adder_pad);
  }
  g_slice_free (PadInfos, infos);
}
