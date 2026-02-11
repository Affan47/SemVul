_e_fm_op_copy_stat_info(E_Fm_Op_Task *task)
{
   struct utimbuf ut;

   if (!task->dst.name) return;

   chmod(task->dst.name, task->src.st.st_mode);
   chown(task->dst.name, task->src.st.st_uid, task->src.st.st_gid);
   ut.actime = task->src.st.st_atime;
   ut.modtime = task->src.st.st_mtime;
   utime(task->dst.name, &ut);
}
