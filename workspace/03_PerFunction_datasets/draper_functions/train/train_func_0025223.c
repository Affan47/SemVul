tree_output()
{
     Symbol **symbols, *main_sym;
     size_t i, num;
     cflow_depmap_t depmap;


     num = collect_functions(&symbols);
     for (i = 0; i < num; i++)
	  symbols[i]->ord = i;


     depmap = depmap_alloc(num);
     for (i = 0; i < num; i++) {
	  if (symbols[i]->callee) {
	       struct linked_list_entry *p;

	       for (p = linked_list_head(symbols[i]->callee); p;
		    p = p->next) {
		    Symbol *s = (Symbol*) p->data;
		    if (symbol_is_function(s))
			 depmap_set(depmap, i, ((Symbol*)p->data)->ord);
	       }
	  }
     }

     depmap_tc(depmap);


     for (i = 0; i < num; i++)
	  if (depmap_isset(depmap, i, i))
	       symbols[i]->recursive = 1;
     free(depmap);
     free(symbols);


     num = collect_symbols(&symbols, is_var, 0);
     qsort(symbols, num, sizeof(*symbols), compare);


     begin();

     if (reverse_tree) {
	  for (i = 0; i < num; i++) {
	       inverted_tree(0, 0, symbols[i]);
	       separator();
	  }
     } else {
	  main_sym = lookup(start_name);
	  if (main_sym) {
	       direct_tree(0, 0, main_sym);
	       separator();
	  } else {
	       for (i = 0; i < num; i++) {
		    if (symbols[i]->callee == NULL)
			 continue;
		    direct_tree(0, 0, symbols[i]);
		    separator();
	       }
	  }
     }

     end();

     free(symbols);
}
