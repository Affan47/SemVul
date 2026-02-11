link_global_array_to_whole_array(Array_table *atbl, Module_table *module,
				  List *whole_array)
 {
     List *li1;
     List *tmp_li = NULL;
     Array_member *am = NULL, *new_am;
     int count = 0;

     for (li1 = whole_array; li1 != NULL; li1 = li1->next) {
	 tmp_li = li1->data;
	 am = tmp_li->data;
	 if (am->array_entry == atbl->entry) {
	     new_am = construct_array_member(module, atbl->entry);
	     tmp_li = list_append(tmp_li, new_am);
	     count++;
	 }
     }
 }
