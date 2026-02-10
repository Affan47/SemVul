SSL_pthreads_locking_callback(int mode, int type, char *file, int line)
{
  if( my.debug == 4 ){
    fprintf(
      stderr,"thread=%4d mode=%s lock=%s %s:%d\n", (int)CRYPTO_thread_id(),
      (mode&CRYPTO_LOCK)?"l":"u", (type&CRYPTO_READ)?"r":"w",file,line
    );
  }
  if(mode & CRYPTO_LOCK){
    pthread_mutex_lock(&(lock_cs[type]));
    lock_count[type]++;
  }
  else{
    pthread_mutex_unlock(&(lock_cs[type]));
  }
}
