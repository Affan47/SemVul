getParamAttributes(unsigned Index) const {
  return pImpl && hasAttributes(Index) ?
    AttributeSet::get(pImpl->getContext(),
                      ArrayRef<std::pair<unsigned, AttributeSetNode*> >(
                        std::make_pair(Index, getAttributes(Index)))) :
    AttributeSet();
}
