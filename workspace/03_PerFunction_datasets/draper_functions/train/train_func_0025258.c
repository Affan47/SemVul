test_lWhat_lSelect(void)
{
   bool ret = true;
   lEnumeration *what = lWhat("%T(%I %I -> %T( %I %I -> %T (%I %I %I %I) %I %I) %I -> %T(%I) %I)",
                              TEST_Type,
                                 TEST_int,
                                 TEST_list, TEST1_Type,
                                    TEST1_int,
                                    TEST1_list, TEST_Type,
                                       TEST_int,
                                       TEST_list,
                                       TEST_object,
                                       TEST_string,
                                    TEST1_object,
                                    TEST1_string,
                                 TEST_object, TEST1_Type,
                                    TEST1_string,
                                 TEST_string);
   lListElem *elem;
   lListElem *elem1;
   lList *list = lCreateList("", TEST_Type);
   lList *list1 = NULL;
   int i;

   elem = lCreateElem(TEST_Type);
   lSetInt(elem, TEST_int, 0);
   lSetHost(elem, TEST_host, "zero");
   lSetString(elem, TEST_string, "zero");
   lSetFloat(elem, TEST_float, 0);
   lSetDouble(elem, TEST_double, 0);
   lSetChar(elem, TEST_char, 'z');
   lSetLong(elem, TEST_long, 0);
   lSetUlong(elem, TEST_ulong, 0);
   lSetBool(elem, TEST_bool, false);

   elem1 = lCreateElem(TEST1_Type);
   lSetInt(elem1, TEST1_int, 1);
   lSetHost(elem1, TEST1_host, "one");
   lSetString(elem1, TEST1_string, "one");
   lSetFloat(elem1, TEST1_float, 1);
   lSetDouble(elem1, TEST1_double, 1);
   lSetChar(elem1, TEST1_char, 'o');
   lSetLong(elem1, TEST1_long, 1);
   lSetUlong(elem1, TEST1_ulong, 1);
   lSetBool(elem1, TEST1_bool, true);

   for (i = 0; i < 5; i++) {
      lList *tmp_list = lCreateList("", TEST1_Type);
      lListElem *tmp_elem = lCopyElem(elem);
      int j;

      for (j = 0; j < 5; j++) {
         lList *tmp_list1 = lCreateList("", TEST_Type);
         lListElem *tmp_elem1 = lCopyElem(elem);
         int k;

         for (k = 0; k < 5; k++) {
            lList *tmp_list2 = lCreateList("", TEST1_Type);
            lListElem *tmp_elem2 = lCopyElem(elem);

            lSetList(tmp_elem2, TEST_list, tmp_list2);
            lAppendElem(tmp_list1, tmp_elem2);
         }

         lSetList(tmp_elem1, TEST_list, tmp_list1);
         lAppendElem(tmp_list, tmp_elem1);
      }

      lSetList(tmp_elem, TEST_list, tmp_list);
      lAppendElem(list, tmp_elem);
   }

   list1 = lSelect("", list, NULL, what);


#if 0
   lWriteListTo(list1, stderr);
#endif

   lFreeWhat(&what);
   lFreeElem(&elem);
   lFreeElem(&elem1);
   lFreeList(&list);
   lFreeList(&list1);

   return ret;
}
