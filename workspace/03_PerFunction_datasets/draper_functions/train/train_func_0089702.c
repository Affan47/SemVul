getSubprogram() const {
  if (auto *Block = dyn_cast<DILexicalBlockBase>(this))
    return Block->getScope()->getSubprogram();
  return const_cast<DISubprogram *>(cast<DISubprogram>(this));
}
