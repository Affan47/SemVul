_tasks_signal_emit(E_Border *border, char *sig, char *src)
{
   const Eina_List *l;
   Tasks *tasks;

   EINA_LIST_FOREACH(tasks_config->tasks, l, tasks)
     {
        const Eina_List *m;
        Tasks_Item *item;

        EINA_LIST_FOREACH(tasks->items, m, item)
          {
             if (item->border == border)
               _tasks_item_signal_emit(item, sig, src);
          }
     }
}
