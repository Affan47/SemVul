json_artifact_for_ci( int rid, char showFiles ){
  cson_value * v = NULL;
  Stmt q = empty_Stmt;
  static cson_value * eventTypeLabel = NULL;
  if(!eventTypeLabel){
    eventTypeLabel = json_new_string("checkin");
    json_gc_add("$EVENT_TYPE_LABEL(commit)", eventTypeLabel);
  }

  db_prepare(&q,
             "SELECT b.uuid, "
             " cast(strftime('%%s',e.mtime) as int), "
             " strftime('%%s',e.omtime),"
             " e.user, "
             " e.comment"
             " FROM blob b, event e"
             " WHERE b.rid=%d"
             "   AND e.objid=%d",
             rid, rid
             );
  if( db_step(&q)==SQLITE_ROW ){
    cson_object * o;
    cson_value * tmpV = NULL;
    const char *zUuid = db_column_text(&q, 0);
    const char *zUser;
    const char *zComment;
    char * zEUser, * zEComment;
    i64 mtime, omtime;
    v = cson_value_new_object();
    o = cson_value_get_object(v);
#define SET(K,V) cson_object_set(o,(K), (V))
    SET("type", eventTypeLabel );
    SET("uuid",json_new_string(zUuid));
    SET("isLeaf", cson_value_new_bool(is_a_leaf(rid)));

    mtime = db_column_int64(&q,1);
    SET("timestamp",json_new_int(mtime));
    omtime = db_column_int64(&q,2);
    if(omtime && (omtime!=mtime)){
      SET("originTime",json_new_int(omtime));
    }

    zUser = db_column_text(&q,3);
    zEUser = db_text(0,
                   "SELECT value FROM tagxref WHERE tagid=%d AND rid=%d",
                   TAG_USER, rid);
    if(zEUser){
      SET("user", json_new_string(zEUser));
      if(0!=fossil_strcmp(zEUser,zUser)){
        SET("originUser",json_new_string(zUser));
      }
      free(zEUser);
    }else{
      SET("user",json_new_string(zUser));
    }

    zComment = db_column_text(&q,4);
    zEComment = db_text(0,
                   "SELECT value FROM tagxref WHERE tagid=%d AND rid=%d",
                   TAG_COMMENT, rid);
    if(zEComment){
      SET("comment",json_new_string(zEComment));
      if(0 != fossil_strcmp(zEComment,zComment)){
        SET("originComment", json_new_string(zComment));
      }
      free(zEComment);
    }else{
      SET("comment",json_new_string(zComment));
    }

    tmpV = json_parent_uuids_for_ci(rid);
    if(tmpV){
      SET("parents", tmpV);
    }

    tmpV = json_tags_for_checkin_rid(rid,0);
    if(tmpV){
      SET("tags",tmpV);
    }

    if( showFiles ){
      tmpV = json_get_changed_files(rid, 1);
      if(tmpV){
        SET("files",tmpV);
      }
    }

#undef SET
  }
  db_finalize(&q);
  return v;
}
