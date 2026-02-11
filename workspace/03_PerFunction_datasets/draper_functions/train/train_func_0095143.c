columnName(int index) const
{
  if (index>=0&&index<numberColumns_) {
    return names_[1][index];
  } else {
    return NULL;
  }
}
