locals_new (DebugManagerPlugin *plugin)
{
	Locals *self = g_new0 (Locals, 1);

	self->plugin = ANJUTA_PLUGIN (plugin);
	self->debugger = dma_debug_manager_get_queue (plugin);

	g_signal_connect_swapped (self->plugin, "program-started", G_CALLBACK (on_program_started), self);

	return self;
}
