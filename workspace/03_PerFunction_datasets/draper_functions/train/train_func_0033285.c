zpixsize(int ptype)
   {


   const int n = sizeof(Zpixtypes)/sizeof(struct Zpixcode);
   int i;
   for(i=0; i<n; i++)
      if(Zpixtypes[i].code == ptype)
	  return(Zpixtypes[i].size);
   return 0;
   }
