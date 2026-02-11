sge_gdi_task_get_operation_name(sge_gdi_task_class_t *task)
{
   const char *ret = NULL;

   switch (task->command) {
      case SGE_GDI_GET:
         ret = "GET";
         break;
      case SGE_GDI_ADD:
         ret = "ADD";
         break;
      case SGE_GDI_DEL:
         ret = "DEL";
         break;
      case SGE_GDI_MOD:
         ret = "MOD";
         break;
      case SGE_GDI_COPY:
         ret = "COPY";
         break;
      case SGE_GDI_TRIGGER:
         ret = "TRIGGER";
         break;
      case SGE_GDI_PERMCHECK:
         ret = "PERMCHECK";
         break;
      case SGE_GDI_REPLACE:
         ret = "REPLACE";
         break;
      default:
         ret = "???";
         break;
   }
   return ret;
}
