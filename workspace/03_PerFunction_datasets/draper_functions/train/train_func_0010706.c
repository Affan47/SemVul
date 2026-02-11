gt_SfxIGetOrigSeq(const void *state, Symbol *dest, unsigned long pos,
                  size_t len)
{
  const struct sfxInterface *sfxi;
  gt_assert(state);
  sfxi = state;
  return EncSeqGetSubSeq(sfxi->encseq, sfxi->readmode, pos, len, dest);
}
