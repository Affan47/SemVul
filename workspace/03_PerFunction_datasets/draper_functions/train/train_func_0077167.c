content_deltify(int rid, int srcid, int force){
  int s;
  Blob data, src, delta;
  Stmt s1, s2;
  int rc = 0;

  if( srcid==rid ) return 0;
  if( !force && findSrcid(rid)>0 ) return 0;
  if( content_is_private(srcid) && !content_is_private(rid) ){
    return 0;
  }
  s = srcid;
  while( (s = findSrcid(s))>0 ){
    if( s==rid ){
      content_undelta(srcid);
      break;
    }
  }
  content_get(srcid, &src);
  if( blob_size(&src)<50 ){
    blob_reset(&src);
    return 0;
  }
  content_get(rid, &data);
  if( blob_size(&data)<50 ){
    blob_reset(&src);
    blob_reset(&data);
    return 0;
  }
  blob_delta_create(&src, &data, &delta);
  if( blob_size(&delta) <= blob_size(&data)*0.75 ){
    blob_compress(&delta, &delta);
    db_prepare(&s1, "UPDATE blob SET content=:data WHERE rid=%d", rid);
    db_prepare(&s2, "REPLACE INTO delta(rid,srcid)VALUES(%d,%d)", rid, srcid);
    db_bind_blob(&s1, ":data", &delta);
    db_begin_transaction();
    db_exec(&s1);
    db_exec(&s2);
    db_end_transaction(0);
    db_finalize(&s1);
    db_finalize(&s2);
    verify_before_commit(rid);
    rc = 1;
  }
  blob_reset(&src);
  blob_reset(&data);
  blob_reset(&delta);
  return rc;
}
