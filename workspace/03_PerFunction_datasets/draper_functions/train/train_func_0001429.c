dynv_set(struct dynvSystem* dynv_system, const char* handler_name, const char* variable_path, const void* value){
	string path(variable_path);
	size_t found;

	struct dynvSystem* dlevel = dynv_system_ref(dynv_system);

	for (;;){
		found = path.find('.');
		if (found != string::npos){
			struct dynvSystem* dlevel_new;
			dlevel_new = (struct dynvSystem*)dynv_system_get(dlevel, "dynv", path.substr(0, found).c_str());
			if (dlevel_new){
				dynv_system_release(dlevel);
				dlevel = dlevel_new;
			}else{
				struct dynvHandlerMap* handler_map = dynv_system_get_handler_map(dynv_system);
				struct dynvSystem* dlevel_new = dynv_system_create(handler_map);
				dynv_handler_map_release(handler_map);

				dynv_system_set(dlevel, "dynv", path.substr(0, found).c_str(), dlevel_new);

				dynv_system_release(dlevel);
				dlevel = dlevel_new;
			}
			path = path.substr(found+1);
		}else break;
	}

	int r = dynv_system_set(dlevel, handler_name, path.c_str(), (void*)value);

	dynv_system_release(dlevel);
	return r;
}
