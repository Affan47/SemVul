link_pipe_elements(struct dtk_pipe_element *source,
			struct dtk_pipe_element *sink)
{
	GstElementClass *klass;
	GList *padlist;
	GstPadTemplate *tpl;


	klass = (GstElementClass *) G_OBJECT_GET_CLASS(source->gstelt);
	padlist = gst_element_class_get_pad_template_list(klass);


	for (; padlist != NULL; padlist = padlist->next) {
		tpl = padlist->data;


		if (tpl->direction != GST_PAD_SRC
		    || tpl->presence == GST_PAD_REQUEST)
			continue;

		switch (tpl->presence) {
		case GST_PAD_ALWAYS:
			gst_element_link(source->gstelt, sink->gstelt);
			return;

		case GST_PAD_SOMETIMES:
			g_signal_connect(source->gstelt, "pad-added",
					 G_CALLBACK(newpad_callback),
					 sink->gstelt);
			return;
		default:
			break;
		}
	}
}
