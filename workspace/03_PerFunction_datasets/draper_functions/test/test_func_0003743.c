updateWalletAfterReorg(BtcWallet & wlt)
{

   for(uint32_t i=0; i<wlt.getTxLedger().size(); i++)
   {
      HashString const & txHash = wlt.getTxLedger()[i].getTxHash();
      if(txJustInvalidated_.count(txHash) > 0)
         wlt.getTxLedger()[i].setValid(false);

      if(txJustAffected_.count(txHash) > 0)
         wlt.getTxLedger()[i].changeBlkNum(getTxByHash(txHash)->getBlockHeight());
   }


   map<OutPoint, TxIOPair>::iterator txioIter;
   for(txioIter  = wlt.getTxIOMap().begin();
       txioIter != wlt.getTxIOMap().end();
       txioIter++)
   {
      pair<bool, bool> reassessValid = txioIter->second.reassessValidity();
      bool txoutIsValid = reassessValid.first;
      bool txinIsValid  = reassessValid.second;

      if(txoutIsValid)
      {
         if(txinIsValid)
            wlt.getUnspentOutPoints().erase(txioIter->first);
         else
            wlt.getUnspentOutPoints().insert(txioIter->first);
      }
      else
      {
         if(txinIsValid)
            cout << "***ERROR: Invalid TxOut but valid TxIn!?" << endl;
         else
            wlt.getUnspentOutPoints().erase(txioIter->first);
      }
   }


   for(uint32_t a=0; a<wlt.getNumAddr(); a++)
   {
      BtcAddress & addr = wlt.getAddrByIndex(a);
      for(uint32_t i=0; i<addr.getTxLedger().size(); i++)
      {
         HashString const & txHash = addr.getTxLedger()[i].getTxHash();
         if(txJustInvalidated_.count(txHash) > 0)
            addr.getTxLedger()[i].setValid(false);

         if(txJustAffected_.count(txHash) > 0)
            addr.getTxLedger()[i].changeBlkNum(getTxByHash(txHash)->getBlockHeight());
      }
   }
}
