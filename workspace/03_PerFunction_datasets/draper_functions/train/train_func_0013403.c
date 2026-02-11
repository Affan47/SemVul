ShowInfo(const Configuration &config)
{


   switch (main_scheduler->ShowStatusCode())
   {

      case (Scheduler::Scheduler_DBError):
         main_scheduler->GetDB()->DisplayError();
         reportError("Database error");
         break;


      case (Scheduler::Scheduler_MemoryError):
         reportError(strerror(errno));
         break;


      case (Scheduler::Scheduler_Interrupted):
      case (Scheduler::Scheduler_OK):
         break;
   }


   switch (main_scheduler->ShowBrokenLinks())
   {

      case (Scheduler::Scheduler_DBError):
         main_scheduler->GetDB()->DisplayError();
         reportError("Database error");
         break;


      case (Scheduler::Scheduler_MemoryError):
         reportError(strerror(errno));
         break;


      case (Scheduler::Scheduler_Interrupted):
      case (Scheduler::Scheduler_OK):
         break;
   }


   if (config.Boolean("summary_anchor_not_found"))
   switch (main_scheduler->ShowAnchorNotFound())
   {

      case (Scheduler::Scheduler_DBError):
         main_scheduler->GetDB()->DisplayError();
         reportError("Database error");
         break;


      case (Scheduler::Scheduler_MemoryError):
         reportError(strerror(errno));
         break;


      case (Scheduler::Scheduler_Interrupted):
      case (Scheduler::Scheduler_OK):
         break;
   }


   switch (main_scheduler->ShowContentTypesPerServer())
   {

      case (Scheduler::Scheduler_DBError):
         main_scheduler->GetDB()->DisplayError();
         reportError("Database error");
         break;


      case (Scheduler::Scheduler_MemoryError):
         reportError(strerror(errno));
         break;


      case (Scheduler::Scheduler_Interrupted):
      case (Scheduler::Scheduler_OK):
         break;
   }

}
