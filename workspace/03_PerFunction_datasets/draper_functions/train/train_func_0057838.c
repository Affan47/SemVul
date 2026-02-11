movq(Register dst, Handle<Object> value, RelocInfo::Mode mode) {


  if (mode == RelocInfo::NONE) {


    ASSERT(value->IsSmi());
    movq(dst, reinterpret_cast<int64_t>(*value), RelocInfo::NONE);
  } else {
    EnsureSpace ensure_space(this);
    ASSERT(value->IsHeapObject());
    ASSERT(!HEAP->InNewSpace(*value));
    emit_rex_64(dst);
    emit(0xB8 | dst.low_bits());
    emitq(reinterpret_cast<uintptr_t>(value.location()), mode);
  }
}
