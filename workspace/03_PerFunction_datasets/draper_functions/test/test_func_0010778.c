readBlkFile_FromScratch(string filename,
                                                           bool doOrganize)
{
   PDEBUG("Read blkfile from scratch");
   blkfilePath_ = filename;
   cout << "Attempting to read blockchain from file: " << blkfilePath_.c_str() << endl;
   ifstream is(blkfilePath_.c_str(), ios::in | ios::binary);
   if( !is.is_open() )
   {
      cout << "***ERROR:  Cannot open " << blkfilePath_.c_str() << endl;
      cerr << "***ERROR:  Cannot open " << blkfilePath_.c_str() << endl;
      return 0;
   }


   is.seekg(0, ios::end);
   uint64_t filesize = (size_t)is.tellg();
   is.seekg(0, ios::beg);
   cout << blkfilePath_.c_str() << " is " << filesize/(float)(1024*1024) << " MB" << endl;


   TIMER_START("ReadBlockchainIntoRAM");
   blockchainData_ALL_.resize(filesize);
   is.read((char*)blockchainData_ALL_.getPtr(), filesize);
   is.close();
   TIMER_STOP("ReadBlockchainIntoRAM");


   PDEBUG("Scanning all block data currently in RAM");


   BinaryRefReader brr(blockchainData_ALL_);
   uint32_t nBlkRead = 0;
   bool keepGoing = true;

   TIMER_START("ScanBlockchainInRAM");
   while(keepGoing)
   {
      keepGoing = parseNewBlockData(brr, totalBlockchainBytes_);
      nBlkRead++;
   }
   TIMER_STOP("ScanBlockchainInRAM");


   totalBlockchainBytes_ = blockchainData_ALL_.getSize();
   lastEOFByteLoc_       = blockchainData_ALL_.getSize();;


   if(doOrganize)
      organizeChain();


   return nBlkRead;
}
