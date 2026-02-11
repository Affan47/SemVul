hdmi_vendor_any_infoframe_pack(union hdmi_vendor_any_infoframe *frame,
			   void *buffer, size_t size)
{

	if (frame->any.oui != HDMI_IEEE_OUI)
		return -EINVAL;

	return hdmi_vendor_infoframe_pack(&frame->hdmi, buffer, size);
}
