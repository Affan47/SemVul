showStatus() const
{
   unsigned short dummy[] = { 0, 0, 0 };
   unsigned short* cseed = seed48(dummy);
   std::cout << std::endl;
   std::cout << "-------- DRand48 engine status ---------" << std::endl;
   std::cout << " Initial seed  = " << theSeed << std::endl;
   std::cout << " Current seeds = " << cseed[0] << ", ";
   std::cout                        << cseed[1] << ", ";
   std::cout                        << cseed[2] << std::endl;
   std::cout << "----------------------------------------" << std::endl;
   for (int i=0; i<3; ++i)
     dummy[i] = cseed[i];
   seed48(dummy);
}
