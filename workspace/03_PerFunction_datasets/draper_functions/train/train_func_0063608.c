test_reserved_names(void){
  int i;
  const char *z;
  int omitRepo = find_option("omitrepo",0,0)!=0;
  db_must_be_within_tree();
  for(i=0; (z = fossil_reserved_name(i, omitRepo))!=0; i++){
    fossil_print("%3d: %s\n", i, z);
  }
  fossil_print("ALL: (%s)\n", fossil_all_reserved_names(omitRepo));
}
