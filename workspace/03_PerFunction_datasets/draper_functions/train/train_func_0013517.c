bcmdec_flush_gstrbuf_queue(GstBcmDec *bcmdec)
{
	GSTBUF_LIST *gst_queue_element = NULL;

	while (1) {
		gst_queue_element = bcmdec_rem_padbuf(bcmdec);
		if (gst_queue_element) {
			if (gst_queue_element->gstbuf) {
				gst_buffer_unref (gst_queue_element->gstbuf);
				bcmdec_put_que_mem_buf(bcmdec, gst_queue_element);
			} else {
				break;
			}
		}
		else {
			GST_DEBUG_OBJECT(bcmdec, "no gst_queue_element");
			break;
		}
	}
}
