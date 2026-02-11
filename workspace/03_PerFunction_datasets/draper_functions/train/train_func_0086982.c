parse_table_cell(
  struct Blob *ob,
  struct render *rndr,
  char *data,
  size_t size,
  int flags
){
  struct Blob fallback = BLOB_INITIALIZER;
  struct Blob *span = new_work_buffer(rndr);

  if( span ){
    parse_inline(span, rndr, data, size);
  }else{
    blob_init(&fallback, data, size);
  }
  rndr->make.table_cell(ob, span ? span : &fallback, flags, rndr->make.opaque);
  release_work_buffer(rndr, span);
}
