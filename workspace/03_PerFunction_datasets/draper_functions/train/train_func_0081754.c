checkfile(std::string &name,DirEntry &info,DirEntry::object_info_level mode) {
  if(plug) {
    plug->error_description="";
    std::string dname=remove_head_dir_s(name,point.length());
    return plug->checkfile(dname,info,mode);
  };
  return 1;
}
