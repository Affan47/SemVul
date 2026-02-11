isLoadOfStoredAddress(uint64_t LoadSize, int64_t LoadOffset,
  const Value *LoadValue) const {
  for (unsigned i = 0, e = NumStores; i != e; ++i) {

    if (LoadValue == StoreValue[i] && LoadOffset == StoreOffset[i])
      return true;


    if (StoreValue[i] == LoadValue) {


      if (StoreOffset[i] < LoadOffset) {
        if (int64_t(StoreOffset[i]+StoreSize[i]) > LoadOffset) return true;
      } else {
        if (int64_t(LoadOffset+LoadSize) > StoreOffset[i]) return true;
      }
    }
  }
  return false;
}
