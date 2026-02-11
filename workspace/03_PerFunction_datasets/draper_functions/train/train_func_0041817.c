StringToTemplateFile(const string& s) {
  static int filenum = 0;
  char buf[16];
  snprintf(buf, sizeof(buf), "%03d", ++filenum);
  string filename = PathJoin(g_tmpdir ? g_tmpdir : "",
                             string("template.") + buf);
  StringToFile(s, filename);
  return filename;
}
