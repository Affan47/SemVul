OpenSSLInit(void) {
    Glib::Mutex::Lock flock(lock);
    if(!initialized) {
      if(!PersistentLibraryInit("modcrypto")) {
        logger().msg(WARNING, "Failed to lock arccrypto library in memory");
      };
      SSL_load_error_strings();
      if(!SSL_library_init()){
        logger().msg(ERROR, "Failed to initialize OpenSSL library");
        HandleOpenSSLError();
        ERR_free_strings();
        return false;
      };


    };

    int num_locks = CRYPTO_num_locks();
    if(num_locks > 0) {
      if(num_locks != ssl_locks_num) {
        if(ssl_locks_num > 0) {
          logger().msg(ERROR, "Number of OpenSSL locks changed - reinitializing");
          ssl_locks_num=0;
          ssl_locks=NULL;
        };
      };
      if((!ssl_locks) || (!initialized)) {
        ssl_locks_num=0;
        ssl_locks=new Glib::Mutex[num_locks];
      };
      if(!ssl_locks) return false;
      ssl_locks_num=num_locks;
      CRYPTO_set_locking_callback(&ssl_locking_cb);
      CRYPTO_set_id_callback(&ssl_id_cb);

    }
    if(!initialized) {
      OpenSSL_add_all_algorithms();
    }
    new OpenSSLThreadCleaner;
    initialized=true;
    return true;
  }
