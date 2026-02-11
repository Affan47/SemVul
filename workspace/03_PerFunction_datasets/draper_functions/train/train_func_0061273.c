dynv_system_set_handler_map(struct dynvSystem* dynv_system, struct dynvHandlerMap* handler_map){
	if (dynv_system->handler_map!=NULL){
		dynv_handler_map_release(dynv_system->handler_map);
		dynv_system->handler_map=NULL;
	}
	if (handler_map!=NULL){
		dynv_system->handler_map=dynv_handler_map_ref(handler_map);
	}
}
