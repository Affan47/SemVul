setVariableIntern(int vnr, int wert, int op) {
  CASSERT(mDatenLaenge == ld->mLevelKnoten->getDatenLaenge());
  CASSERT(vnr >= 0 && vnr < ld->mLevelKnoten->getDatenLaenge());

  int oldValue = mDaten[vnr];

  switch (op) {
    case set_code: mDaten[vnr] = wert; break;
    case add_code: mDaten[vnr] += wert; break;
    case sub_code: mDaten[vnr] -= wert; break;
    case mul_code: mDaten[vnr] *= wert; break;
    case div_code: mDaten[vnr] = divv(mDaten[vnr],wert); break;
    case mod_code: mDaten[vnr] = modd(mDaten[vnr],wert); break;
    case bitset_code: mDaten [vnr] |= wert; break;
    case bitunset_code: mDaten [vnr] &= (-1-wert); break;
    default:


      throw iFehler(_("Internal error in Blop::setVariable() (op = %d)"),
                   op);
  }


  switch (vnr) {
    case spezvar_kind:
      if (mDaten[vnr] < blopart_min_cual || mDaten[vnr] >= ld->mAnzFarben)


        throw Fehler(_("Value %d for kind out of range (allowed: %d - %d)"),
	             mDaten[vnr], blopart_min_cual, ld->mAnzFarben - 1);
      break;
  }

  if ((vnr==spezvar_kind) && (mDaten[vnr]!=oldValue))
    setKindIntern(mDaten[vnr]);
}
