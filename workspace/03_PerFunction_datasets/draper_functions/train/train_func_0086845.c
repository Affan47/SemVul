aspell_speller_suggest(Speller * ths, const char * word, int word_size)
{
  ths->temp_str_0.clear();
  ths->to_internal_->convert(word, word_size, ths->temp_str_0);
  unsigned int s0 = ths->temp_str_0.size();
  PosibErr<const WordList *> ret = ths->suggest(MutableString(ths->temp_str_0.mstr(), s0));
  ths->err_.reset(ret.release_err());
  if (ths->err_ != 0) return 0;
  if (ret.data)
    const_cast<WordList *>(ret.data)->from_internal_ = ths->from_internal_;
  return ret.data;
}
