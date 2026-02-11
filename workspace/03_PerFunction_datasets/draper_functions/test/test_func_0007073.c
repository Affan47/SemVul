allowCalc(){


  if ( !couplingsPtr->isSUSY ) return false;


  if ( !settingsPtr->flag("SLHA:useDecayTable") ) return true;


  for ( int iDec = 1; iDec < int((coupSUSYPtr->slhaPtr)->decays.size()); ++iDec)
    if ( (coupSUSYPtr->slhaPtr)->decays[iDec].getId() == abs(idRes) ) {
      if (DBSUSY) cout<<"Using external decay table for:"<<idRes<<endl;
      return false;
    }


  return true;
}
