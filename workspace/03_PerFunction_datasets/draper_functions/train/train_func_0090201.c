contains(const ImmutableComparison &other)
  const
{
  _check_comparison_compatibility(this, &other);

  ImmutableComparison * sub = other.subtract(*this);
  bool answer;

  if (sub->is_empty()) {
    answer = true;
  } else {
    answer = false;
  }

  delete sub;
  return answer;
}
