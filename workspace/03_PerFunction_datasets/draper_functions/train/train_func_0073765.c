_tasks_refill_all(void)
{
   const Eina_List *l;
   Tasks *tasks;

   EINA_LIST_FOREACH(tasks_config->tasks, l, tasks)
     {
        _tasks_refill(tasks);
     }
}
