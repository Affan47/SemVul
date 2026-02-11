_e_fm_op_rollback(E_Fm_Op_Task *task)
{
   E_Fm_Op_Copy_Data *data;

   if (!task) return;

   if (task->type == E_FM_OP_COPY)
     {
        data = task->data;
        if (data)
          {
             if (data->from)
               {
                  fclose(data->from);
                  data->from = NULL;
               }
             if (data->to)
               {
                  fclose(data->to);
                  data->to = NULL;
               }
          }
        E_FREE(task->data);
        _e_fm_op_update_progress(task, -task->dst.done,
                                 -task->src.st.st_size - (task->link ? REMOVECHUNKSIZE : 0));
     }
   else
     _e_fm_op_update_progress(task, -REMOVECHUNKSIZE, -REMOVECHUNKSIZE);
}
