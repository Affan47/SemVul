go_undo_binary_finalize (GObject *o)
{
	GOUndoBinary *ua = (GOUndoBinary *)o;

	if (ua->disposea)
		ua->disposea (ua->a);
	if (ua->disposeb)
		ua->disposeb (ua->b);

	G_OBJECT_CLASS (go_undo_binary_parent_class)->finalize (o);
}
