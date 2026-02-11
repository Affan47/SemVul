fso_framework_inotifier_onActionFromInotify (FsoFrameworkINotifier* self, GIOChannel* source, GIOCondition condition) {
	gboolean result = FALSE;
	GIOCondition _tmp0_ = 0;
	GIOCondition _tmp2_ = 0;
	GIOCondition _tmp10_ = 0;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (source != NULL, FALSE);
	_tmp0_ = condition;
	if ((_tmp0_ & G_IO_HUP) == G_IO_HUP) {
		FsoFrameworkLogger* _tmp1_ = NULL;
		_tmp1_ = fso_framework_theLogger;
		fso_framework_logger_error (_tmp1_, "HUP on inotify, will no longer get any notifications");
		result = FALSE;
		return result;
	}
	_tmp2_ = condition;
	if ((_tmp2_ & G_IO_IN) == G_IO_IN) {
		gint _tmp3_ = 0;
		gchar* _tmp4_ = NULL;
		gint _tmp4__length1 = 0;
		gint _tmp5_ = 0;
		gchar* _tmp6_ = NULL;
		gint _tmp6__length1 = 0;
		struct inotify_event* pevent = NULL;
		gchar* _tmp7_ = NULL;
		gint _tmp7__length1 = 0;
		struct inotify_event* _tmp8_ = NULL;
		struct inotify_event _tmp9_ = {0};
		_tmp3_ = self->priv->fd;
		_vala_assert (_tmp3_ != (-1), "fd != -1");
		_tmp4_ = self->priv->buffer;
		_tmp4__length1 = self->priv->buffer_length1;
		_vala_assert (_tmp4_ != NULL, "buffer != null");
		_tmp5_ = self->priv->fd;
		_tmp6_ = self->priv->buffer;
		_tmp6__length1 = self->priv->buffer_length1;
		read (_tmp5_, _tmp6_, (gsize) FSO_FRAMEWORK_INOTIFIER_BUFFER_LENGTH);
		_tmp7_ = self->priv->buffer;
		_tmp7__length1 = self->priv->buffer_length1;
		pevent = (struct inotify_event*) _tmp7_;
		_tmp8_ = pevent;
		_tmp9_ = *_tmp8_;
		fso_framework_inotifier_handleEvent (self, &_tmp9_);
		result = TRUE;
		return result;
	}
	_tmp10_ = condition;
	g_critical ("inotifier.vala:98: Unsupported IOCondition %u", (guint) ((gint) _tmp10_));
	result = TRUE;
	return result;
}
