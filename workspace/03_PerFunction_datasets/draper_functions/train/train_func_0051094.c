fluid_synth_update_mixer(fluid_synth_t* synth, void* method, int intparam,
                         fluid_real_t realparam)
{
	fluid_return_if_fail(synth != NULL || synth->eventhandler != NULL);
	fluid_return_if_fail(synth->eventhandler->mixer != NULL);
	fluid_rvoice_eventhandler_push(synth->eventhandler, method,
	                               synth->eventhandler->mixer,
	                               intparam, realparam);
}
