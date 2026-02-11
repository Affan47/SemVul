butEnv_addFile(ButEnv *env, int group, int fd, void *packet,
		     ButOut (*callback)(void *packet, int fd))  {
  int  i;

  assert((group >= 0) && (group < 3));
  if (fd >= env->maxFd)
    env->maxFd = fd + 1;
  if (fd >= env->maxGFds[group])  {
    ButFdCallback *newFc = wms_malloc((fd+1)*sizeof(ButFdCallback));
    for (i = 0;  i < env->maxGFds[group];  ++i)
      newFc[i] = env->fCallbacks[group][i];
    for (;  i < fd;  ++i)
      newFc[i].callback = NULL;
    if (env->fCallbacks[group] != NULL)
      wms_free(env->fCallbacks[group]);
    env->maxGFds[group] = fd + 1;
    env->fCallbacks[group] = newFc;
  }
  env->fCallbacks[group][fd].callback = callback;
  env->fCallbacks[group][fd].packet = packet;
  FD_SET(fd, &env->fMasks[group]);
}
