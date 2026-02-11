CalcSkipProba(uint64_t nb, uint64_t total) {
  return (int)(total ? (total - nb) * 255 / total : 255);
}
