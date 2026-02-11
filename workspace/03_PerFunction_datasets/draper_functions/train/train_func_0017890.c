instance_mark_lhier_diffs(
  funit_inst* root1,
  funit_inst* root2
) { PROFILE(INSTANCE_MARK_LHIER_DIFFS);


  while( (root1 != NULL) && (root2 != NULL) && (strcmp( root1->name, root2->name ) == 0) ) {
    root1 = root1->parent;
    root2 = root2->parent;
  }


  while( root1 != NULL ) {
    root1->suppl.name_diff = TRUE;
    root1 = root1->parent;
  }

  PROFILE_END;

}
