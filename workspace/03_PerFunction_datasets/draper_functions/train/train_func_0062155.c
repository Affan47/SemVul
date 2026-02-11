createRNG(const Pass* P) const {
  SmallString<32> Salt(P->getPassName());


  Salt += sys::path::filename(getModuleIdentifier());

  return new RandomNumberGenerator(Salt);
}
