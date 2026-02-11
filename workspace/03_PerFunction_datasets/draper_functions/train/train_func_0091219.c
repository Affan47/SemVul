operator()(const TestProperty& test_property) const {
    return String(test_property.key()).Compare(key_) == 0;
  }
