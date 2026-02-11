TokenizeAndEncode(const string& line, vector<int>& encoded) {
  for (util::TokenIter<util::AnyCharacter, true> it(line, util::AnyCharacter(" "));
       it; ++it) {
    if (!m_enable_preserve_case) {
      string token = it->as_string();
      for (std::string::iterator sit = token.begin();
           sit != token.end(); ++sit) {
        *sit = tolower(*sit);
      }
      encoded.push_back(m_vocab->Encode(token));
    } else {
      encoded.push_back(m_vocab->Encode(it->as_string()));
    }
  }
}
