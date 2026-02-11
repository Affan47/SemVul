gst_accurip_reset (GstAccurip * accurip)
{
  if (accurip->num_samples != 0) {


    accurip->is_first = FALSE;
    accurip->is_last = FALSE;
    ring_free (accurip);
  }
  accurip->crc = 0;
  accurip->crc_v2 = 0;

  accurip->num_samples = 0;
}
