uv_fs_fdatasync(uv_loop_t* loop, uv_fs_t* req, uv_file file, uv_fs_cb cb) {
  char* path = NULL;
#if defined(__FreeBSD__) \
  || (__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ < 1060)


  WRAP_EIO(UV_FS_FDATASYNC, eio_fdatasync, fsync, ARGS1(file))
#else
  WRAP_EIO(UV_FS_FDATASYNC, eio_fdatasync, fdatasync, ARGS1(file))
#endif
}
