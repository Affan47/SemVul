bcmdec_send_buff_detect_error(GstBcmDec *bcmdec, GstBuffer *buf,
						   guint8* pbuffer, guint32 size,
						   guint32 offset, GstClockTime tCurrent,
						   guint8 flags)
{
	BC_STATUS sts = BC_STS_SUCCESS;
	GstMapInfo info;

	GST_DEBUG_OBJECT(bcmdec, "Attempting to Send Buffer");

	sts = decif_send_buffer(&bcmdec->decif, pbuffer, size, tCurrent, flags);

	if (sts != BC_STS_SUCCESS) {
	        gst_buffer_map(buf, &info, GST_MAP_READ);
		GST_ERROR_OBJECT(bcmdec, "proc input failed sts = %d", sts);
		GST_ERROR_OBJECT(bcmdec, "Chain: timeStamp = %llu size = %d data = %p",
				 GST_BUFFER_DTS(buf), info.size, info.data);
		gst_buffer_unmap(buf, &info);
		return GST_FLOW_ERROR;
	}

	return GST_FLOW_OK;
}
