sslContext_locking_callback(int mode, int type, const char *,int) {

  if (mode & CRYPTO_LOCK) {
    openssl_locks[type].lock();
  }
  else {
    OMNIORB_ASSERT(mode & CRYPTO_UNLOCK);
    openssl_locks[type].unlock();
  }
}
