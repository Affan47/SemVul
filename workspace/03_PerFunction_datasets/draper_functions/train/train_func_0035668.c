cleanup(int g)
{
#ifndef FAKEROOT_FAKENET
  union semun sem_union;
#endif

  if(debug)
    fprintf(stderr, FAKEROOT_CLEANUPMSG,  g);

#ifndef FAKEROOT_FAKENET
  msgctl (msg_get, IPC_RMID,NULL);
  msgctl (msg_snd, IPC_RMID,NULL);
  semctl (sem_id,0,IPC_RMID,sem_union);
#endif

  save(0);

  if(g!=-1)
    exit(0);
}
