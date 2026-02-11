print(raw_ostream &OS) const {
  OS << "LSR Use: Kind=";
  switch (Kind) {
  case Basic:    OS << "Basic"; break;
  case Special:  OS << "Special"; break;
  case ICmpZero: OS << "ICmpZero"; break;
  case Address:
    OS << "Address of ";
    if (AccessTy->isPointerTy())
      OS << "pointer";
    else
      OS << *AccessTy;
  }

  OS << ", Offsets={";
  for (SmallVectorImpl<int64_t>::const_iterator I = Offsets.begin(),
       E = Offsets.end(); I != E; ++I) {
    OS << *I;
    if (llvm::next(I) != E)
      OS << ',';
  }
  OS << '}';

  if (AllFixupsOutsideLoop)
    OS << ", all-fixups-outside-loop";

  if (WidestFixupType)
    OS << ", widest fixup type: " << *WidestFixupType;
}
