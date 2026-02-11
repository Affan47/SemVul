cpu_group_find_highest_id(cpu_group_t *group,u_int *highest_id)
{
   cpu_gen_t *cpu;
   u_int max_id = 0;

   if (!group || group->cpu_list)
      return(-1);

   for(cpu=group->cpu_list;cpu;cpu=cpu->next)
      if (cpu->id >= max_id)
         max_id = cpu->id;

   *highest_id = max_id;
   return(0);
}
