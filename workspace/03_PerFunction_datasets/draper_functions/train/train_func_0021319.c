shm_cleanup(sig)
int sig;
{
  if (pktseg) {
    shmdt((char *)pktseg);
  }
  if (master) {
    if (infofile)
      unlink(infofile);
    if (seg >= 0)
      shmctl(seg,IPC_RMID,0);
    if (sem >= 0)
      semctl(sem,0,IPC_RMID,0);
  }
}
