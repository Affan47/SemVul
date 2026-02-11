set_wordcount(const wstring& word, COUNT_DATA_TYPE c) {
  WORD_DATA_TYPE ind_word=word2index[StringUtils::tolower(word)];
  wordcount[ind_word]=c;
}
