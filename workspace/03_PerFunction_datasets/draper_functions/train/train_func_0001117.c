sichtbaresUpdaten() {
  for (int i = mAnimZeigVon; i < mAnimZeigBis; i++)
    mEintraege[i]->setUpdateFlag();
  mRaenderUpdaten = true;
  mInfozeileUpdaten = true;
}
