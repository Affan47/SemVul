get(const ArrayType* T, Constant* const* Vals,
                             unsigned NumVals) {

  return get(T, std::vector<Constant*>(Vals, Vals+NumVals));
}
