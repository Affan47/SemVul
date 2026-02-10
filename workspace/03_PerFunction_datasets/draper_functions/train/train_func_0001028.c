_e_fm_ipc_handle_error_response(int id, E_Fm_Op_Type type)
{
   E_Fm_Task *task = _e_fm_ipc_task_get(id);
   E_Fm_Slave *slave = NULL;

   if (!task)
     {
        slave = _e_fm_ipc_slave_get(id);
        if (slave) _e_fm_ipc_slave_send(slave, type, NULL, 0);
        return;
     }

   if (type == E_FM_OP_ERROR_RESPONSE_ABORT)
     {
        _e_fm_ipc_task_remove(task);
     }
   else if (type == E_FM_OP_ERROR_RESPONSE_RETRY)
     {
        switch (task->type)
          {
           case E_FM_OP_MKDIR:
             _e_fm_ipc_mkdir_try(task);
             break;

           case E_FM_OP_MONITOR_START:
             _e_fm_ipc_monitor_start_try(task);

           default:
             break;
          }
     }
}
