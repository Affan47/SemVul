Failed(string Message,pkgAcquire::MethodConfig *Cnf)
{
   string Final = _config->FindDir("Dir::State::lists") + URItoFileName(RealURI);


   if(Status == StatTransientNetworkError)
   {
      Item::Failed(Message,Cnf);

      if(FileExists(LastGoodSig))
 	 Rename(LastGoodSig,Final);


      Status = pkgAcquire::Item::StatTransientNetworkError;
      return;
   }


   unlink(Final.c_str());


   new pkgAcqMetaIndex(Owner, MetaIndexURI, MetaIndexURIDesc, MetaIndexShortDesc,
		       "", IndexTargets, MetaIndexParser);

   if (Cnf->LocalOnly == true ||
       StringToBool(LookupTag(Message,"Transient-Failure"),false) == false)
   {

      Status = StatDone;
      Complete = false;
      Dequeue();
      return;
   }

   Item::Failed(Message,Cnf);
}
