db_merge_instance_trees() { PROFILE(DB_MERGE_INSTANCE_TREES);

  funit_inst* base  = NULL;
  inst_link*  instl;
  bool        done  = FALSE;

  if( db_list != NULL ) {


    instl = db_list[curr_db]->inst_head;
    while( instl != NULL ) {
      if( strcmp( instl->inst->name, "$root" ) == 0 ) {
        if( base == NULL ) {
          base        = instl->inst;
          instl->base = TRUE;
        } else {
          instl->ignore = instance_merge_two_trees( base, instl->inst );
        }
      }
      instl = instl->next;
    }


    while( !done ) {
      base  = NULL;
      instl = db_list[curr_db]->inst_head;
      while( instl != NULL ) {
        if( strcmp( instl->inst->name, "$root" ) != 0 ) {
          if( !instl->ignore && !instl->base ) {
            if( base == NULL ) {
              base        = instl->inst;
              instl->base = TRUE;
            } else {
              instl->ignore = instance_merge_two_trees( base, instl->inst );
            }
          }
        }
        instl = instl->next;
      }
      done = (base == NULL);
    }

  } else {

    print_output( "Attempting to merge unscored CDDs", FATAL, __FILE__, __LINE__ );
    Throw 0;

  }

  PROFILE_END;

}
