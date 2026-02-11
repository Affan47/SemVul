job_run_sequence_verify(int pos, const char *all_jobids[], int *order[])
{
   int test_index, i, j;
   int found_group = 0;
   int *group;


   for (i=0; order[i]; i++) {
      group = order[i];
      for (j=0; group[j] != -1; j++) {
         if (group[j] == pos) {
            found_group = 1;
            break;
         }
      }
      if (found_group)
         break;
   }
   if (!found_group) {
      fprintf(stderr, "test broken: could not find job index %d in finish order scheme\n", pos);
      return -1;
   }


   while (i>0) {
      i--;
      for (j=0; order[i][j] != -1; j++) {
         test_index = order[i][j];
         if (all_jobids[test_index] != NULL) {
            fprintf(stderr, "order broken: job \"%s\" [%d] did not finish before job \"%s\" [%d]\n",
                  all_jobids[test_index], test_index, all_jobids[pos], pos);
            return -1;
         }
      }
   }

   return 0;
}
