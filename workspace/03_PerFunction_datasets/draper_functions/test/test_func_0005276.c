scanNonStdTx(uint32_t blknum,
                             uint32_t txidx,
                             TxRef&   tx,
                             uint32_t txoutidx,
                             BtcAddress& thisAddr)
{
   TxOutRef txout = tx.getTxOutRef(txoutidx);
   int findIdx = txout.getScriptRef().find(thisAddr.getAddrStr20());
   if(findIdx > -1)
   {
      cout << "ALERT:  Found non-standard transaction referencing" << endl;
      cout << "        an address in your wallet.  There is no way" << endl;
      cout << "        for this program to determine if you can" << endl;
      cout << "        spend these BTC or not.  Please email the" << endl;
      cout << "        following information to etotheipi@gmail.com" << endl;
      cout << "        for help identifying the transaction and how" << endl;
      cout << "        to spend it:" << endl;
      cout << endl;
      cout << "   Block Number: " << blknum << endl;
      cout << "   Tx Hash:      " << tx.getThisHash().copySwapEndian().toHexStr()
                               << " (BE)" << endl;
      cout << "   TxOut Index:  " << txoutidx << endl;
      cout << "   PubKey Hash:  " << thisAddr.getAddrStr20().toHexStr()
                               << " (LE)" << endl;
      cout << "   RawScript:    " << endl;
      BinaryDataRef scr = txout.getScriptRef();
      uint32_t sz = scr.getSize();
      for(uint32_t i=0; i<sz; i+=32)
      {
         if( i < sz-32 )
            cout << "      " << scr.getSliceCopy(i,sz-i).toHexStr();
         else
            cout << "      " << scr.getSliceCopy(i,32).toHexStr();
      }
      cout << endl;
      cout << "   Attempting to interpret script:" << endl;
      BtcUtils::pprintScript(scr);
      cout << endl;


      OutPoint outpt(tx.getThisHash(), txoutidx);
      nonStdUnspentOutPoints_.insert(outpt);
      pair< map<OutPoint, TxIOPair>::iterator, bool> insResult;
      pair<OutPoint, TxIOPair> toBeInserted(outpt, TxIOPair(&tx,txoutidx));
      insResult = nonStdTxioMap_.insert(toBeInserted);
      insResult = txioMap_.insert(toBeInserted);
   }

}
