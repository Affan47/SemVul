_e_fm_ipc_monitor_start(int id, const char *path)
{
   E_Fm_Task *task = malloc(sizeof(E_Fm_Task));

   if (!task) return;

   task->id = id;
   task->type = E_FM_OP_MONITOR_START;
   task->slave = NULL;
   task->src = eina_stringshare_add(path);
   task->dst = NULL;
   task->rel = NULL;
   task->rel_to = 0;
   task->x = 0;
   task->y = 0;

   _e_fm_tasks = eina_list_append(_e_fm_tasks, task);

   _e_fm_ipc_monitor_start_try(task);
}
