fso_framework_async_worker_queue_finalize (GObject* obj) {
	FsoFrameworkAsyncWorkerQueue * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, FSO_FRAMEWORK_TYPE_ASYNC_WORKER_QUEUE, FsoFrameworkAsyncWorkerQueue);
	_g_queue_free0 (self->q);
	(self->worker_target_destroy_notify == NULL) ? NULL : (self->worker_target_destroy_notify (self->worker_target), NULL);
	self->worker = NULL;
	self->worker_target = NULL;
	self->worker_target_destroy_notify = NULL;
	G_OBJECT_CLASS (fso_framework_async_worker_queue_parent_class)->finalize (obj);
}
