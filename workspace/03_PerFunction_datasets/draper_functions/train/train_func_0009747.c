add_group(const std::string& grp) {
  groups_.push_back(group_t(grp,default_vo_,default_role_,default_capability_,default_vgroup_,default_voms_));
  logger.msg(Arc::VERBOSE,"Assigned to authorization group %s",grp);
}
