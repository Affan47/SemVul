inner_product(const FVector& rhs) const {
    CHECK(m_coreFeatures.size() == rhs.m_coreFeatures.size());
    FValue product = 0.0;
    for (const_iterator i = cbegin(); i != cend(); ++i) {
        product += ((i->second)*(rhs.get(i->first)));
    }
    for (size_t i = 0; i < m_coreFeatures.size(); ++i) {
      product += m_coreFeatures[i]*rhs.m_coreFeatures[i];
    }
    return product;
  }
