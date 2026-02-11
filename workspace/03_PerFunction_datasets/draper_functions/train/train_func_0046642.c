destruct_whole_array(List *whole_array)
 {
     List *li1, *li2;
     List *tmp_li = NULL;
     Array_member *am = NULL;

     for (li1 = whole_array; li1 != NULL; li1 = li1->next) {
	 tmp_li = li1->data;
	 for (li2 = tmp_li; li2 != NULL; li2 = li2->next) {
	     am = li2->data;
	     free(am);
	 }
	 list_free(tmp_li);
     }
     list_free(whole_array);
 }
