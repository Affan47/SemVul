print_func_def(ast *a){
	#ifdef GEN_TEST_DEBUG
	printf("<printing FUNC_DEF>");
	#endif
	if (a->data.func_def.thread_generated == 0){
		print_func_def_nominal(a);
	} else {
		print_func_def_thread_gen(a);
	}
}
