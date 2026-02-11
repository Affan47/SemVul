operator<<(std::ostream &out, const TreeInput &input)
{
  out<< static_cast<Phrase const&>(input) << " ||| ";

  size_t size = input.GetSize();
  for (size_t startPos = 0; startPos < size; ++startPos) {
    for (size_t endPos = startPos; endPos < size; ++endPos) {
      const NonTerminalSet &labelSet = input.GetLabelSet(startPos, endPos);
      NonTerminalSet::const_iterator iter;
      for (iter = labelSet.begin(); iter != labelSet.end(); ++iter) {
        const Word &word = *iter;
        out << "[" << startPos <<"," << endPos << "]="
            << word << "(" << word.IsNonTerminal() << ") ";
        CHECK(word.IsNonTerminal());
      }
    }
  }

  return out;
}
