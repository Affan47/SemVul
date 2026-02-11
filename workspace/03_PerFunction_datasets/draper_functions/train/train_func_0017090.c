URIStart(FetchResult &Res)
{
   if (Queue == 0)
      abort();

   std::cout << "200 URI Start\n"
	     << "URI: " << Queue->Uri << "\n";
   if (Res.Size != 0)
      std::cout << "Size: " << Res.Size << "\n";

   if (Res.LastModified != 0)
      std::cout << "Last-Modified: " << TimeRFC1123(Res.LastModified) << "\n";

   if (Res.ResumePoint != 0)
      std::cout << "Resume-Point: " << Res.ResumePoint << "\n";

   if (UsedMirror.empty() == false)
      std::cout << "UsedMirror: " << UsedMirror << "\n";

   std::cout << "\n" << std::flush;
}
