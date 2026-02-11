fluid_rvoice_eventhandler_push_ptr(fluid_rvoice_eventhandler_t* handler,
                                   void* method, void* object, void* ptr)
{
	fluid_rvoice_event_t* event;
	fluid_rvoice_event_t local_event;
	event = handler->is_threadsafe ?
	        fluid_ringbuffer_get_inptr(handler->queue, handler->queue_stored) : &local_event;

	if (event == NULL) {
		FLUID_LOG(FLUID_WARN, "Ringbuffer full, try increasing polyphony!");
		return FLUID_FAILED;
	}

	event->method = method;
	event->object = object;
	event->ptr = ptr;
	if (handler->is_threadsafe)
		handler->queue_stored++;
	else
		fluid_rvoice_event_dispatch(event);
	return FLUID_OK;
}
