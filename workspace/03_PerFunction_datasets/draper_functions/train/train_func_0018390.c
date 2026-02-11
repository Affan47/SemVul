AllocateProxy(Address proxy, PretenureFlag pretenure) {

  STATIC_ASSERT(Proxy::kSize <= Page::kMaxHeapObjectSize);
  AllocationSpace space = (pretenure == TENURED) ? OLD_DATA_SPACE : NEW_SPACE;
  Object* result;
  { MaybeObject* maybe_result = Allocate(proxy_map(), space);
    if (!maybe_result->ToObject(&result)) return maybe_result;
  }

  Proxy::cast(result)->set_proxy(proxy);
  return result;
}
