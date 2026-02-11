merge_registers(void)
{
   int *last_reads = rzalloc_array(mem_ctx, int, this->next_temp);
   int *first_writes = rzalloc_array(mem_ctx, int, this->next_temp);
   int i, j;


   for (i=0; i < this->next_temp; i++) {
      last_reads[i] = get_last_temp_read(i);
      first_writes[i] = get_first_temp_write(i);
   }


   for (i=0; i < this->next_temp; i++) {

      if (last_reads[i] < 0 || first_writes[i] < 0) continue;

      for (j=0; j < this->next_temp; j++) {

         if (last_reads[j] < 0 || first_writes[j] < 0) continue;


         if (first_writes[i] <= first_writes[j] &&
             last_reads[i] <= first_writes[j])
         {
            rename_temp_register(j, i);


            last_reads[i] = last_reads[j];
            first_writes[j] = -1;
            last_reads[j] = -1;
         }
      }
   }

   ralloc_free(last_reads);
   ralloc_free(first_writes);
}
