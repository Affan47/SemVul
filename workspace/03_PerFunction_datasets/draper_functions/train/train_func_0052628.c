gst_rtp_mpa_pay_reset (GstRtpMPAPay * pay)
{
  pay->first_ts = -1;
  pay->duration = 0;
  gst_adapter_clear (pay->adapter);
  GST_DEBUG_OBJECT (pay, "reset depayloader");
}
