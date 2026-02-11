run_test(long nr) {
   int test_result = 0;
   printf("running test for issue %ld - %s\n", issue_list[nr], issue_desc[nr]);
   switch (issue_list[nr]) {
      case 2728: {
         test_result = issue_2728_test();
         break;
      }
      default: {
         printf("Unknown issue %ld\n", issue_list[nr]);
         test_result = 1;
         break;
      }
   }

   if (test_result == 0) {
      printf("ok!\n");
   } else {
      printf("failed!\n");
   }
   return test_result;
}
