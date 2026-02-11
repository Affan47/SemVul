uv_fs_readlink(uv_loop_t* loop, uv_fs_t* req, const char* path,
    uv_fs_cb cb) {
  ssize_t size;
  int status;
  char* buf;

  status = -1;

  uv_fs_req_init(loop, req, UV_FS_READLINK, path, cb);

  if (cb) {
    if ((req->eio = eio_readlink(path, EIO_PRI_DEFAULT, uv__fs_after, req))) {
      uv_ref(loop);
      return 0;
    } else {
      uv__set_sys_error(loop, ENOMEM);
      return -1;
    }
  } else {


    if ((size = pathconf(path, _PC_PATH_MAX)) == -1) {
#if defined(PATH_MAX)
      size = PATH_MAX;
#else
      size = 4096;
#endif
    }

    if ((buf = malloc(size + 1)) == NULL) {
      uv__set_sys_error(loop, ENOMEM);
      return -1;
    }

    if ((size = readlink(path, buf, size)) == -1) {
      req->errorno = errno;
      req->result = -1;
      free(buf);
    } else {

      buf = realloc(buf, size + 1);
      buf[size] = '\0';
      req->result = 0;
      req->ptr = buf;
    }

    return req->result;
  }

  assert(0 && "unreachable");
}
