_gcr_certificate_renderer_append_distinguished_name (GcrRenderer *renderer,
                                                     GcrDisplayView *view,
                                                     GNode *dn)
{
	AppendDnClosure closure;

	g_return_if_fail (GCR_IS_RENDERER (renderer));
	g_return_if_fail (GCR_IS_DISPLAY_VIEW (view));
	g_return_if_fail (dn != NULL);

	closure.renderer = renderer;
	closure.view = view;
	egg_dn_parse (dn, on_parsed_dn_part, &closure);
}
