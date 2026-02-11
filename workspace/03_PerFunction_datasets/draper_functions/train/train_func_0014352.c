_tasks_free(Tasks *tasks)
{
   Tasks_Item *item;
   EINA_LIST_FREE(tasks->items, item)
     _tasks_item_free(item);
   evas_object_del(tasks->o_items);
   free(tasks);
}
