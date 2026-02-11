cleanup () {
  set<int> dep_files;
  _frepo.dependent (_primary, dep_files);
  _jprepo.cleanup (dep_files);
  _advrepo.cleanup (dep_files);
  _asprepo.cleanup (dep_files);
  _frepo.cleanup (_primary);
}
