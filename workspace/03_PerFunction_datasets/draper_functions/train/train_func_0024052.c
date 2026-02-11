update_processing_task_context_free (UpdateProcessingTaskContext *ctxt)
{
	g_free (ctxt->urn);
	g_free (ctxt->parent_urn);

	if (ctxt->cancellable) {
		g_object_unref (ctxt->cancellable);
	}

	if (ctxt->builder) {
		g_object_unref (ctxt->builder);
	}

	g_slice_free (UpdateProcessingTaskContext, ctxt);
}
