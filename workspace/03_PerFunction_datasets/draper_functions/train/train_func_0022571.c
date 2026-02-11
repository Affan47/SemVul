MoveConnectionHere(Fish *o)
{
   super::MoveConnectionHere(o);
   rate_limit=o->rate_limit.borrow();
   path_queue.MoveHere(o->path_queue);
   RespQueue.move_here(o->RespQueue);
   timeout_timer.Reset(o->timeout_timer);
   set_real_cwd(o->real_cwd);
   state=CONNECTED;
   o->Disconnect();
   if(!home)
      set_home(home_auto);
   ResumeInternal();
}
