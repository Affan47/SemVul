string_array_find_caseblind_(  double *string_array_header,
			            char *test_string,
                                    int *test_len,
                                    int *result_array,
                                    int *result_array_size,
                                    int *num_indices
                                  )
{
   int i,j=0;
   int true_test_len, true_model_len, array_size,
       string_size, hash_value, result_array_size1;
   SA_Head * head;
   List_Node *bucket, *p;
   char * model_string;
   int match=0, is_quoted=0;


   if(*(SA_Head**)string_array_header){
      head = *((SA_Head**)string_array_header);
      array_size = head->array_size;
      string_size = head->string_size;

      tm_get_strlen_(&true_test_len, test_len, test_string);


      hash_value = string_array_hash(test_string, true_test_len, 0, array_size);


      if(true_test_len ==0){
	 result_array_size1 = 5;
      }
      else {
	 result_array_size1 = *result_array_size;
      }

      bucket = head->hash_table[hash_value];

      for(p=bucket; p; p=p->next) {
	  model_string=&(head->string_array[(p->index-1)*string_size]);
          string_array_get_strlen_(string_array_header, &(p->index), &true_model_len);

          match = 0;

          if(true_model_len == true_test_len){
	     match = 1;
	     for( i=0; i<true_model_len; i++){
		 if(uc(test_string[i])!=uc(model_string[i])){
		    match = 0;
                    break;
		 }
	     }
	  }


          if(match==1){
	      if(j<result_array_size1){
		 result_array[j]=p->index;
                 j++;
	      }
              else{
                 break;
	      }
	  }
      }
   }
   else{
       printf("\nString array not initialized yet!");
   }
   *num_indices = j;
}
