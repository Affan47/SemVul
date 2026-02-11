IncreasePriority(int i, int new_priority) {
  if (new_priority < vec_[i])
    return false;
  vec_[i] = new_priority;
  while (i > 0 && vec_[Parent(i)] < vec_[i]) {
    std::swap(vec_[Parent(i)], vec_[i]);
    i = Parent(i);
  }
  return true;
}
