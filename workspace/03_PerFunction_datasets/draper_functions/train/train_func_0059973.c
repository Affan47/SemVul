user_make_sess(USER *user){
  assert(user);
  if(pthread_mutex_lock(&(user->mutex)) != 0) return;
  if(user->sess) cbmapclose(user->sess);
  user->sess = cbmapopenex(MINIBNUM);
  pthread_mutex_unlock(&(user->mutex));
}
