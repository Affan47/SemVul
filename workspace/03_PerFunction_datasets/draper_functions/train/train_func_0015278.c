pars_sql(

	pars_info_t*	info,
	const char*	str)
{
	sym_node_t*	sym_node;
	mem_heap_t*	heap;
	que_t*		graph;

	ut_ad(str);

	heap = mem_heap_create(16000);


	ut_ad(mutex_own(&(dict_sys->mutex)));

	pars_sym_tab_global = sym_tab_create(heap);

	pars_sym_tab_global->string_len = strlen(str);
	pars_sym_tab_global->sql_string = mem_heap_dup(
		heap, str, pars_sym_tab_global->string_len + 1);
	pars_sym_tab_global->next_char_pos = 0;
	pars_sym_tab_global->info = info;

	yyparse();

	sym_node = UT_LIST_GET_FIRST(pars_sym_tab_global->sym_list);

	while (sym_node) {
		ut_a(sym_node->resolved);

		sym_node = UT_LIST_GET_NEXT(sym_list, sym_node);
	}

	graph = pars_sym_tab_global->query_graph;

	graph->sym_tab = pars_sym_tab_global;
	graph->info = info;


	return(graph);
}
