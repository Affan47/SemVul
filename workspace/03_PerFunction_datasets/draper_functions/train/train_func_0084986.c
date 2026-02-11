uv_fs_ftruncate(uv_loop_t* loop,
                    uv_fs_t* req,
                    uv_file file,
                    int64_t off,
                    uv_fs_cb cb) {
  INIT(FTRUNCATE);
  req->file = file;
  req->off = off;
  POST;
}
