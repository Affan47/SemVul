dma_sparse_buffer_class_init (DmaSparseBufferClass * klass)
{
	GObjectClass *object_class;

	g_return_if_fail (klass != NULL);

	parent_class = g_type_class_peek_parent (klass);

	object_class = G_OBJECT_CLASS (klass);

	object_class->dispose = dma_sparse_buffer_dispose;
	object_class->finalize = dma_sparse_buffer_finalize;

	klass->changed = on_dma_sparse_buffer_changed;

	signals[CHANGED] = g_signal_new ("changed",
									 G_OBJECT_CLASS_TYPE (object_class),
									 G_SIGNAL_RUN_LAST,
									 G_STRUCT_OFFSET (DmaSparseBufferClass, changed),
									 NULL, NULL,
									 anjuta_marshal_VOID__VOID,
									 G_TYPE_NONE,
									 0);
}
