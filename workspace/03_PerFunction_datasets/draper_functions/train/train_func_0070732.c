GetModifierForXml(HtmlParser* htmlparser,
                                                        string* error_msg) {
  vector<const ModifierAndValue*> modvals;
  modvals.push_back(g_am_dirs[AM_XML]);
  return modvals;
}
