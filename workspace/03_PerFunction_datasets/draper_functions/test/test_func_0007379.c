getY(int a) const {
  if (!existiert(a)) return blop_pos_nix;
  return mPos.getY(a, mSpf->getHochVerschiebung());
}
