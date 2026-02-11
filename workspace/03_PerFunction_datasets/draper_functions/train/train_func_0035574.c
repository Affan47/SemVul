GetTargetPhraseCollection(InputType const& src,WordsRange const& range) const
{
  return GetTargetPhraseCollection(src.GetSubString(range));
}
