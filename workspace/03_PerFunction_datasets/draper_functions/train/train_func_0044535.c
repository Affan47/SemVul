mimetype_test_cmd(void){
  int i;
  for(i=2; i<g.argc; i++){
    fossil_print("%-20s -> %s\n", g.argv[i], mimetype_from_name(g.argv[i]));
  }
}
