dynv_system_set(struct dynvSystem* dynv_system, const char* handler_name, const char* variable_name, void* value){
	struct dynvVariable* variable=NULL;
	struct dynvHandler* handler=NULL;

	if (handler_name!=NULL){
		dynvHandlerMap::HandlerMap::iterator j;
		j=dynv_system->handler_map->handlers.find(handler_name);
		if (j==dynv_system->handler_map->handlers.end()){
			return -3;
		}else{
			handler=(*j).second;
		}
	}

	dynvSystem::VariableMap::iterator i;
	i=dynv_system->variables.find(variable_name);
	if (i==dynv_system->variables.end()){
		if (handler==NULL) return -2;
		variable=dynv_variable_create(variable_name, handler);
		dynv_system->variables[variable->name]=variable;
		variable->handler->create(variable);
		return variable->handler->set(variable, value, false);
	}else{
		variable=(*i).second;
	}

	if (variable->flags & dynvVariable::READONLY) return -4;

	if (variable->handler==handler){
		return variable->handler->set(variable, value, false);
	}else{
		if (handler->create!=NULL){
			dynv_variable_destroy_data(variable);
			variable->handler=handler;
			variable->handler->create(variable);
			return variable->handler->set(variable, value, false);
		}
	}
	return -1;
}
