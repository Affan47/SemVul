Failed(string Message,pkgAcquire::MethodConfig * )
{
   if(Debug)
      std::clog << "pkgAcqSubIndex failed: " << Desc.URI << " with " << Message << std::endl;

   Complete = false;
   Status = StatDone;
   Dequeue();


}
