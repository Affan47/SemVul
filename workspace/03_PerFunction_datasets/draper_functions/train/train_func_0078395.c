ggobi_renderer_flush (GGobiRenderer * self, GdkGC * gc, gint xsrc, gint ysrc, gint xdest, gint ydest, gint width, gint height)
{
#line 481 "ggobi-renderer.c"
	GGobiRendererClass *klass;
#line 57 "renderer.gob"
	g_return_if_fail (self != NULL);
#line 57 "renderer.gob"
	g_return_if_fail (GGOBI_IS_RENDERER (self));
#line 487 "ggobi-renderer.c"
	klass = GGOBI_RENDERER_GET_CLASS(self);

	if(klass->flush)
		(*klass->flush)(self,gc,xsrc,ysrc,xdest,ydest,width,height);
}
