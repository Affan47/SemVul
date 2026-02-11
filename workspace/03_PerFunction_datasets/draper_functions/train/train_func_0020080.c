uv__fs_write(uv_fs_t* req) {
  ssize_t r;


#if defined(__APPLE__)
  static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&lock);
#endif

  if (req->off < 0)
    r = write(req->file, req->buf, req->len);
  else
    r = pwrite(req->file, req->buf, req->len, req->off);

#if defined(__APPLE__)
  pthread_mutex_unlock(&lock);
#endif

  return r;
}
