pushd(const char * dir){
  int ret = 0;
  char * pwd;
  if((pwd = getcwd(NULL,0)) == NULL){return 1;}
  if(dir == NULL){
    if(root == NULL){return 1;}
    else{
      char * top = stack_pop(root);
      root = stack_push(root,pwd);
      printf("%s ", top);
      print_stack(root);
      printf("\n");
      return cd(top);
    }
  }
  else {
    ret = cd(dir);
    char * new_dir;
    if((new_dir = getcwd(NULL,0)) == NULL){return 1;}
    root = stack_push(root,pwd);
    printf("%s ", new_dir);
    print_stack(root);
    printf("\n");
    return ret;
  }
}
