dma_disassemble_new(DebugManagerPlugin *plugin)
{
	DmaDisassemble* self;

	self = g_new0 (DmaDisassemble, 1);

	self->plugin = plugin;
	self->debugger = dma_debug_manager_get_queue (plugin);;

	g_signal_connect_swapped (self->plugin, "program-loaded", G_CALLBACK (on_program_loaded), self);

	return self;
}
