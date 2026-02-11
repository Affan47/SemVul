usesTextureCache(unsigned Opcode) const {
  return (!ST.hasVertexCache() && IS_VTX(get(Opcode))) || IS_TEX(get(Opcode));
}
