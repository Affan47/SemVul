get_resource_info(u_long32 resource, const char **name,
                             int *resource_type)
{
   int is_job_resource_column;
   int row;

#if defined(NECSX4) || defined(NECSX5)
   is_job_resource_column = 0;
#else
   is_job_resource_column = 1;
#endif

   row = 0;
   while (resource_table[row].resource_name) {
      if (resource == resource_table[row].resource) {
         *name = resource_table[row].resource_name;
         *resource_type =
            resource_table[row].resource_type[is_job_resource_column];
         return 0;
      }
      row++;
   }
   *name = unknown_string;
   return 1;
}
