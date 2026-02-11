verifyBlkFileIntegrity(void)
{
   PDEBUG("Verifying blk0001.dat integrity");
   bool isGood = true;
   map<HashString, BlockHeaderRef>::iterator headIter;
   for(headIter  = headerHashMap_.begin();
       headIter != headerHashMap_.end();
       headIter++)
   {
      BlockHeaderRef & bhr = headIter->second;
      bool thisHeaderIsGood = bhr.verifyIntegrity();
      if( !thisHeaderIsGood )
      {
         cout << "Blockfile contains incorrect header or tx data:" << endl;
         cout << "  Block number:    " << bhr.getBlockHeight() << endl;
         cout << "  Block hash (BE):   " << endl;
         cout << "    " << bhr.getThisHash().copySwapEndian().toHexStr() << endl;
         cout << "  Num Tx :         " << bhr.getNumTx() << endl;
         cout << "  Tx Hash List: (compare to raw tx data on blockexplorer)" << endl;
         for(uint32_t t=0; t<bhr.getNumTx(); t++)
            cout << "    " << bhr.getTxRefPtrList()[t]->getThisHash().copySwapEndian().toHexStr() << endl;
      }
      isGood = isGood && thisHeaderIsGood;
   }
   return isGood;
   PDEBUG("Done verifying blockfile integrity");
}
