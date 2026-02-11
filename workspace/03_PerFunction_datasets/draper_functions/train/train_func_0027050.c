createDefaultPBQPRegisterAllocator() {
  if (pbqpCoalescing) {
    return createPBQPRegisterAllocator(
             std::auto_ptr<PBQPBuilder>(new PBQPBuilderWithCoalescing()));
  }
  return createPBQPRegisterAllocator(
           std::auto_ptr<PBQPBuilder>(new PBQPBuilder()));
}
