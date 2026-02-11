gtkcellrendererpixbuf_gtk_pixbuf_render_set_lazy_loader(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj cell_renderer_scm;
  GtkCellRendererPixbuf* cell_renderer;
  ScmObj handler_scm;
  ScmProcedure* handler;
  ScmObj SCM_SUBRARGS[2];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-pixbuf-render-set-lazy-loader");
  for (SCM_i=0; SCM_i<2; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  cell_renderer_scm = SCM_SUBRARGS[0];
  if (!SCM_GTK_CELL_RENDERER_PIXBUF_P(cell_renderer_scm)) Scm_Error("<gtk-cell-renderer-pixbuf> required, but got %S", cell_renderer_scm);
  cell_renderer = SCM_GTK_CELL_RENDERER_PIXBUF(cell_renderer_scm);
  handler_scm = SCM_SUBRARGS[1];
  if (!SCM_PROCEDUREP(handler_scm)) Scm_Error("procedure required, but got %S", handler_scm);
  handler = SCM_PROCEDURE(handler_scm);
  {

GClosure *closure = Scm_MakeGClosure(handler);


GValue gv1 = {0,};
g_value_init(&gv1,G_TYPE_OBJECT);
g_value_set_object(&gv1, NULL);
g_object_set_property((GObject*)cell_renderer, "pixbuf", &gv1);


GValue gv = {0,};
g_value_init(&gv,G_TYPE_POINTER);

#if 0
Scm_Warn("%s start\n",__FUNCTION__);
#endif

g_value_set_pointer(&gv, (gpointer) closure);

g_object_set_property((GObject*)cell_renderer, "lazy-load", &gv);

#if 0
Scm_Warn("%s end\n",__FUNCTION__);
#endif


SCM_RETURN(SCM_UNDEFINED);
  }
}
