test_search_forward_backward(void) {
   bool ret = true;
   sge_sl_list_t *list = NULL;

   DENTER(TOP_LAYER, "test_search_forward_backward");


   ret = sge_sl_create(&list);


   if (ret) {
      ret &= sge_sl_insert(list, "ax", SGE_SL_BACKWARD);
      ret &= sge_sl_insert(list, "bx", SGE_SL_BACKWARD);
      ret &= sge_sl_insert(list, "Xa", SGE_SL_BACKWARD);
      ret &= sge_sl_insert(list, "Xb", SGE_SL_BACKWARD);
      ret &= sge_sl_insert(list, "ex", SGE_SL_BACKWARD);
      ret &= sge_sl_insert(list, "fx", SGE_SL_BACKWARD);
      ret &= sge_sl_insert(list, "Xc", SGE_SL_BACKWARD);
      ret &= sge_sl_insert(list, "hx", SGE_SL_BACKWARD);
      ret &= sge_sl_insert(list, "ix", SGE_SL_BACKWARD);
      ret &= sge_sl_insert(list, "Xd", SGE_SL_BACKWARD);
   }

   if (ret) {
      char *data = NULL;

      ret &= sge_sl_data_search(list, "X*", (void *)&data,
                                test_compare_first_char, SGE_SL_FORWARD);
      if (strcmp(data, "Xa") != 0) {
         fprintf(stderr, "Error: Expected %s as search result but got %s "
                 "in function %s()\n", "Xa", data, SGE_FUNC);
         ret = false;
      }
   }


   if (ret) {
      ret &= test_search_sequence(list, true, "X*", "XaXbXcXd", 10, SGE_FUNC);
      ret &= test_search_sequence(list, false, "X*", "XdXcXbXa", 10, SGE_FUNC);
   }

   if (ret) {
      ret &= sge_sl_destroy(&list, test_destroy_test);
   }

   DRETURN(ret);
}
