substitute(const std::string& orig, const int a, const int b, const std::string& c) {
  gchar *tmp_str = g_strdup_printf(orig.c_str(), a, b, c.c_str());
  std::string final_str(tmp_str);
  g_free(tmp_str);
  return final_str;
}
