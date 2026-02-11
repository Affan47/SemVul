AtomicMul(volatile sys::cas_flag* ptr, sys::cas_flag val) {
  sys::cas_flag original, result;
  do {
    original = *ptr;
    result = original * val;
  } while (sys::CompareAndSwap(ptr, result, original) != original);

  return result;
}
