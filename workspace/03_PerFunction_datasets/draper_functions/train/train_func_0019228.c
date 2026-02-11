operator<(const Cie& cie1, const Cie& cie2)
{
  if (cie1.personality_name_ != cie2.personality_name_)
    return cie1.personality_name_ < cie2.personality_name_;
  return cie1.contents_ < cie2.contents_;
}
