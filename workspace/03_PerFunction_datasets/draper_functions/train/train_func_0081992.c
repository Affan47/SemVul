main(void)
{
   BlockDataManager_FullRAM & bdm = BlockDataManager_FullRAM::GetInstance();


   cout << "Reading data from blockchain..." << endl;
   TIMER_START("BDM_Load_and_Scan_BlkChain");
   bdm.readBlkFile_FromScratch("../../blk0001.dat");


   TIMER_STOP("BDM_Load_and_Scan_BlkChain");
   cout << endl << endl;


   cout << endl << "Organizing blockchain: " ;
   TIMER_START("BDM_Organize_Chain");
   bool isGenOnMainChain = bdm.organizeChain();
   TIMER_STOP("BDM_Organize_Chain");
   cout << (isGenOnMainChain ? "No Reorg!" : "Reorg Detected!") << endl;
   cout << endl << endl;


   cout << "Printing genesis block information:" << endl;
   bdm.getGenesisBlock().pprint(cout, 0, false);
   cout << endl << endl;

   cout << "Printing last block information:" << endl;
   bdm.getTopBlockHeader().pprint(cout, 0, false);
   cout << endl << endl;


   bdm.findAllNonStdTx();


   BinaryData myAddress;
   BtcWallet wlt;
   myAddress.createFromHex("604875c897a079f4db88e5d71145be2093cae194"); wlt.addAddress(myAddress);
   myAddress.createFromHex("8996182392d6f05e732410de4fc3fa273bac7ee6"); wlt.addAddress(myAddress);
   myAddress.createFromHex("b5e2331304bc6c541ffe81a66ab664159979125b"); wlt.addAddress(myAddress);
   myAddress.createFromHex("ebbfaaeedd97bc30df0d6887fd62021d768f5cb8"); wlt.addAddress(myAddress);
   TIMER_WRAP(bdm.scanBlockchainForTx_FromScratch(wlt));

   cout << "Checking balance of all addresses: " << wlt.getNumAddr() << " addrs" << endl;
   for(uint32_t i=0; i<wlt.getNumAddr(); i++)
   {
      BinaryData addr20 = wlt.getAddrByIndex(i).getAddrStr20();
      cout << "  Addr: " << wlt.getAddrByIndex(i).getBalance() << ","
                         << wlt.getAddrByHash160(addr20).getBalance() << endl;
      vector<LedgerEntry> const & ledger = wlt.getAddrByIndex(i).getTxLedger();
      for(uint32_t j=0; j<ledger.size(); j++)
      {
         cout << "    Tx: "
           << ledger[j].getAddrStr20().getSliceCopy(0,4).toHexStr() << "  "
           << ledger[j].getValue()/(float)(CONVERTBTC) << " ("
           << ledger[j].getBlockNum()
           << ")  TxHash: " << ledger[j].getTxHash().getSliceCopy(0,4).toHexStr() << endl;
      }

   }
   cout << endl << endl;


   UniversalTimer::instance().print();
   UniversalTimer::instance().printCSV("timings.csv");
   cout << endl << endl;


   char pause[256];
   cout << "enter anything to exit" << endl;
   cin >> pause;


}
