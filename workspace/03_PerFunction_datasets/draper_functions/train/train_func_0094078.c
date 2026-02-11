pprintAlot(ostream & os)
{
   cout << "Header:   " << getBlockHeight() << endl;
   cout << "Hash:     " << getThisHash().toHexStr(true)  << endl;
   cout << "Hash:     " << getThisHash().toHexStr(false) << endl;
   cout << "PrvHash:  " << getPrevHash().toHexStr(true)  << endl;
   cout << "PrvHash:  " << getPrevHash().toHexStr(false) << endl;
   cout << "this*:    " << this << endl;
   cout << "TotSize:  " << getBlockSize() << endl;
   vector<TxRef*> txlist = getTxRefPtrList();
   vector<BinaryData> hashlist = getTxHashList();
   cout << "Number of Tx:  " << txlist.size() << ", " << hashlist.size() << endl;
   for(uint32_t i=0; i<txlist.size(); i++)
      txlist[i]->pprintAlot();

}
