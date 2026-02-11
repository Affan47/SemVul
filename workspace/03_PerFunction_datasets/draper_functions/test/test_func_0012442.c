json_get_changed_files(int rid, int flags){
  cson_value * rowsV = NULL;
  cson_array * rows = NULL;
  Stmt q = empty_Stmt;
  db_prepare(&q,
           "SELECT (pid==0) AS isnew,"
           "       (fid==0) AS isdel,"
           "       (SELECT name FROM filename WHERE fnid=mlink.fnid) AS name,"
           "       blob.uuid as uuid,"
           "       (SELECT uuid FROM blob WHERE rid=pid) as parent,"
           "       blob.size as size"
           "  FROM mlink, blob"
           " WHERE mid=%d AND pid!=fid"
           " AND blob.rid=fid "
           " ORDER BY name /*sort*/",
             rid
             );
  while( (SQLITE_ROW == db_step(&q)) ){
    cson_value * rowV = cson_value_new_object();
    cson_object * row = cson_value_get_object(rowV);
    int const isNew = db_column_int(&q,0);
    int const isDel = db_column_int(&q,1);
    char * zDownload = NULL;
    if(!rowsV){
      rowsV = cson_value_new_array();
      rows = cson_value_get_array(rowsV);
    }
    cson_array_append( rows, rowV );
    cson_object_set(row, "name", json_new_string(db_column_text(&q,2)));
    cson_object_set(row, "uuid", json_new_string(db_column_text(&q,3)));
    if(!isNew && (flags & json_get_changed_files_ELIDE_PARENT)){
      cson_object_set(row, "parent", json_new_string(db_column_text(&q,4)));
    }
    cson_object_set(row, "size", json_new_int(db_column_int(&q,5)));

    cson_object_set(row, "state",
                    json_new_string(json_artifact_status_to_string(isNew,isDel)));
    zDownload = mprintf("/raw/%s?name=%s",

                        db_column_text(&q,2),
                        db_column_text(&q,3));
    cson_object_set(row, "downloadPath", json_new_string(zDownload));
    free(zDownload);
  }
  db_finalize(&q);
  return rowsV;
}
