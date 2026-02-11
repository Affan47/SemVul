print_lock(ast *a){
	#ifdef GEN_TEST_DEBUG
	printf("<printing LOCK>");
	#endif

	ast_list *tmp = a->data.lock.params;
	printf("{\n");


	printf("pthread_mutex_lock( &" MAIN_LOCK_NAME " );\n");

	while (tmp != NULL){
		printf("while (pthread_mutex_trylock( &" MAIN_LOCK_STRUCT_NAME ".mutex_%p ) != 0){\n",
			tmp->data->data.symtab_ptr);
		printf("\tpthread_cond_wait(& %s, & %s);\n}\n", MAIN_COND_NAME, MAIN_LOCK_NAME);
		printf("pthread_cond_signal(& %s);\n", MAIN_COND_NAME);
		tmp = tmp->next;
	}


	printf("pthread_mutex_unlock( &" MAIN_LOCK_NAME " );\n");


	print_ast(a->data.lock.body);


	printf("pthread_mutex_lock( &" MAIN_LOCK_NAME " );\n");

	tmp = a->data.lock.params;
	while (tmp != NULL){
		printf("pthread_mutex_unlock( &" MAIN_LOCK_STRUCT_NAME ".mutex_%p );\n",
			tmp->data->data.symtab_ptr);
		printf("pthread_cond_signal(& %s);\n", MAIN_COND_NAME);
		tmp = tmp->next;
	}


	printf("pthread_mutex_unlock( &" MAIN_LOCK_NAME " );\n");

	printf("\n}\n");
}
