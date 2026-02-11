title_size(GanvModule* module, double* w, double* h)
{
	if (module->box.node.impl->label) {
		g_object_get(G_OBJECT(module->box.node.impl->label),
		             "width", w,
		             "height", h,
		             NULL);
	} else {
		*w = *h = 0.0;
	}
}
