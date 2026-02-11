_e_fm_op_update_progress(E_Fm_Op_Task *task, off_t _plus_e_fm_op_done, off_t _plus_e_fm_op_total)
{


   static off_t _e_fm_op_done = 0, _e_fm_op_total = 0;

   static int ppercent = -1;
   int percent;
   static double c_time = 0;
   static double s_time = 0;
   double eta = 0;
   static int peta = -1;
   static E_Fm_Op_Task *ptask = NULL;

   _e_fm_op_done += _plus_e_fm_op_done;
   _e_fm_op_total += _plus_e_fm_op_total;


   if (_e_fm_op_scan_idler_p) return;

   if (_e_fm_op_total != 0)
     {


        percent = _e_fm_op_done * 100 / _e_fm_op_total % 101;

        eta = peta;

        if (!s_time) s_time = ecore_time_get();


        if ((_e_fm_op_done) && (ecore_time_get() - c_time > 1.0))
          {
             c_time = ecore_time_get();
             eta = (c_time - s_time) * (_e_fm_op_total - _e_fm_op_done) / _e_fm_op_done;
             eta = (int)(eta + 0.5);
          }

        if (!task) return;
        if ((percent != ppercent) || (eta != peta) || (task != ptask))
          {
             ppercent = percent;
             peta = eta;
             ptask = task;
             _e_fm_op_update_progress_report(percent, eta, c_time - s_time,
                                             _e_fm_op_done, _e_fm_op_total,
                                             task->src.name, task->dst.name);
          }
     }
}
