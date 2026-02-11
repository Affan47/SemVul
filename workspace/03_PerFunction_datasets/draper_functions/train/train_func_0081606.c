___finalize(GObject *obj_self)
{
#define __GOB_FUNCTION__ "Gmpc:Stats:Label::finalize"
	GmpcStatsLabel *self G_GNUC_UNUSED = GMPC_STATS_LABEL (obj_self);
	gpointer priv G_GNUC_UNUSED = self->_priv;
#line 47 "gmpc-stats-label.gob"
	if(self->_priv->song) { mpd_freeSong ((gpointer) self->_priv->song); self->_priv->song = NULL; }
#line 106 "gmpc-stats-label.c"
	if(G_OBJECT_CLASS(parent_class)->finalize) \
		(* G_OBJECT_CLASS(parent_class)->finalize)(obj_self);
}
