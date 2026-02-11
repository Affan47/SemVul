gridfs_destroy(gridfs *gfs) {
  if( gfs == NULL ) return;
  if( gfs->dbname ) {
    bson_free((char*)gfs->dbname);
    gfs->dbname = NULL;
  }
  if( gfs->prefix ) {
    bson_free((char*)gfs->prefix);
    gfs->prefix = NULL;
  }
  if( gfs->files_ns ) {
    bson_free((char*)gfs->files_ns);
    gfs->files_ns = NULL;
  }
  if( gfs->chunks_ns ) {
    bson_free((char*)gfs->chunks_ns);
    gfs->chunks_ns = NULL;
  }
}
