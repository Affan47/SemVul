stream_pad_removed_cb (GstElement *decoder, GstPad *pad, RBXFadeStream *stream)
{
	if (pad == stream->decoder_pad) {
		rb_debug ("active output pad for stream %s removed", stream->uri);
		stream->decoder_linked = FALSE;

		gst_object_unref (stream->decoder_pad);
		stream->decoder_pad = NULL;
	}
}
