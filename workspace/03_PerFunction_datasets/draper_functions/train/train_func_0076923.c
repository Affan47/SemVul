oe_exec_switch(CORBA_Object obj, CORBA_Environment *env, oe_map_t *map)
{

    int res = 0;
    int index = 0;


    int length = map->length;
    char* op = env->_operation;

    PRINT_MAP("switching on map", map);


    env->_major = CORBA_NO_EXCEPTION;

    if ((res = oe_prepare_request_decoding(env) < 0))
	return res;
#if defined(DEBUG_MAP)
    fprintf(stdout, "looking for operation: %s\n", op); fflush(stdout);
#endif
    for (index = 0; index < length; index++) {
#if defined(DEBUG_MAP)
	fprintf(stdout, "map->operations[%d].name: %s\n",
		index, map->operations[index].name);
	fflush(stdout);
#endif
	if(strcmp(map->operations[index].name, op) == 0) {
#if defined(DEBUG_MAP)
	    fprintf(stdout, "calling map->operations[%d].function: 0x%X\n",
		    index, map->operations[index].function);
	    fflush(stdout);
#endif
	    return map->operations[index].function(obj, env);
	}
    }

    CORBA_exc_set(env, CORBA_SYSTEM_EXCEPTION, BAD_OPERATION,
		  "Invalid operation");
    return -1;
}
