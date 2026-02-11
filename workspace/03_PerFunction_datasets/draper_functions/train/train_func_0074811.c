GetFlagFileFlag() {
#ifdef _MSC_VER
  static const string flagfile = FLAGS_srcdir + "\\src\\gflags_unittest_flagfile";
#else
  static const string flagfile = FLAGS_srcdir + "/src/gflags_unittest_flagfile";
#endif
  static const string flagfile_flag = string("--flagfile=") + flagfile;
  return flagfile_flag.c_str();
}
