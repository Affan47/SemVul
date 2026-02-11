analyze1(GroupInfo &info,
			    const AndModelGroup *andAncestor,
			    unsigned andGroupIndex,
			    FirstSet &first,
			    LastSet &last)
{
  member(0).analyze(info, andAncestor, andGroupIndex, first, last);
  first.setNotRequired();
  inherentlyOptional_ = member(0).inherentlyOptional();
  for (unsigned i = 1; i < nMembers(); i++) {
    FirstSet tempFirst;
    LastSet tempLast;
    member(i).analyze(info, andAncestor, andGroupIndex, tempFirst, tempLast);
    first.append(tempFirst);
    first.setNotRequired();
    last.append(tempLast);
    inherentlyOptional_ |= member(i).inherentlyOptional();
  }
}
