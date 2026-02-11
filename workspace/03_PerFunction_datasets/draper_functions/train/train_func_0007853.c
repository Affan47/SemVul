OutputAlignment(ostream &out, const AlignmentInfo &ai, size_t sourceOffset, size_t targetOffset)
{
  typedef std::vector< const std::pair<size_t,size_t>* > AlignVec;
  AlignVec alignments = ai.GetSortedAlignments();

  AlignVec::const_iterator it;
  for (it = alignments.begin(); it != alignments.end(); ++it) {
    const std::pair<size_t,size_t> &alignment = **it;
    out << alignment.first + sourceOffset << "-" << alignment.second + targetOffset << " ";
  }

}
