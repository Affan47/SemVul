_e_hints_process_wakeup(E_Border *bd)
{


   if (!bd->client.vkbd.have_property) return;
   if (bd->client.netwm.pid <= 0) return;
#ifdef SIGCHLD
   kill(bd->client.netwm.pid, SIGCHLD);
#endif
}
