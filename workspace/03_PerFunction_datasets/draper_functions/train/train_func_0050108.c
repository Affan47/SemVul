QueueNextDiff()
{


   string FinalFile = _config->FindDir("Dir::State::lists");
   FinalFile += URItoFileName(RealURI);

   FileFd fd(FinalFile, FileFd::ReadOnly);
   SHA1Summation SHA1;
   SHA1.AddFD(fd);
   string local_sha1 = string(SHA1.Result());
   if(Debug)
      std::clog << "QueueNextDiff: "
		<< FinalFile << " (" << local_sha1 << ")"<<std::endl;


   if(local_sha1 == ServerSha1)
   {
      Finish(true);
      return true;
   }


   for(vector<DiffInfo>::iterator I=available_patches.begin();
       available_patches.empty() == false &&
	  I != available_patches.end() &&
	  I->sha1 != local_sha1;
       ++I)
   {
      available_patches.erase(I);
   }


   if(available_patches.empty() == true)
   {
      Failed("", NULL);
      return false;
   }


   Desc.URI = RealURI + ".diff/" + available_patches[0].file + ".gz";
   Desc.Description = Description + " " + available_patches[0].file + string(".pdiff");
   DestFile = _config->FindDir("Dir::State::lists") + "partial/";
   DestFile += URItoFileName(RealURI + ".diff/" + available_patches[0].file);

   if(Debug)
      std::clog << "pkgAcqIndexDiffs::QueueNextDiff(): " << Desc.URI << std::endl;

   QueueURI(Desc);

   return true;
}
