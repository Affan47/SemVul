dma_data_buffer_class_init (DmaDataBufferClass * klass)
{
	GObjectClass *object_class;

	g_return_if_fail (klass != NULL);

	parent_class = G_OBJECT_CLASS (g_type_class_peek_parent (klass));

	object_class = G_OBJECT_CLASS (klass);
	object_class->dispose = dma_data_buffer_dispose;
	object_class->finalize = dma_data_buffer_finalize;

	klass->changed_notify = dma_data_buffer_changed_notify;

	signals[CHANGED_NOTIFY] = g_signal_new ("changed_notify",
									 G_OBJECT_CLASS_TYPE (object_class),
									 G_SIGNAL_RUN_LAST,
									 G_STRUCT_OFFSET (DmaDataBufferClass, changed_notify),
									 NULL, NULL,
									 anjuta_marshal_VOID__ULONG_ULONG,
									 G_TYPE_NONE,
									 2,
									 G_TYPE_ULONG,
									 G_TYPE_ULONG);
}
