allNames(Kind kind, AttributeSeq &seq) const
{
  if (has(kind, Attribute::NORMAL()))
    seq.push_back(Attribute::NORMAL());
  for (int i = 0; i < count(); ++i)
    iSheets[i]->allNames(kind, seq);
}
