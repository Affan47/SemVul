markOrphanChain(BlockHeaderRef & bhpStart)
{
   PDEBUG("Marking orphan chain");
   bhpStart.isMainBranch_ = true;
   map<BinaryData, BlockHeaderRef>::iterator iter;
   iter = headerHashMap_.find(bhpStart.getPrevHash());
   HashStringRef lastHeadHash(32);
   while( iter != headerHashMap_.end() )
   {


      if(iter->second.isMainBranch() == true)
      {
         cout << "***ERROR: Block previously main branch, now orphan!?"
              << iter->second.getThisHash().toHexStr() << endl;
         cerr << "***ERROR: Block previously main branch, now orphan!?"
              << iter->second.getThisHash().toHexStr() << endl;
         previouslyValidBlockHeaderPtrs_.push_back(&(iter->second));
      }
      iter->second.isOrphan_ = true;
      iter->second.isMainBranch_ = false;
      lastHeadHash.setRef(iter->second.thisHash_);
      iter = headerHashMap_.find(iter->second.getPrevHash());
   }
   orphanChainStartBlocks_.push_back(&(headerHashMap_[lastHeadHash.copy()]));
   PDEBUG("Done marking orphan chain");
}
