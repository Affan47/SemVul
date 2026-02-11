on_disconnect (void *data)
{
	VALUE self = (VALUE) data;
	RbXmmsClient *xmms = NULL;

	Data_Get_Struct (self, RbXmmsClient, xmms);

	rb_funcall (xmms->disconnect_cb, rb_intern ("call"), 0);
}
