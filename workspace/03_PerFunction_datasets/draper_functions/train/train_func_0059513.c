VersionState(DepIterator D,unsigned char Check,
				       unsigned char SetMin,
				       unsigned char SetPolicy)
{
   unsigned char Dep = 0xFF;

   while (D.end() != true)
   {

      DepIterator Start = D;
      unsigned char State = 0;
      for (bool LastOR = true; D.end() == false && LastOR == true; ++D)
      {
	 State |= DepState[D->ID];
	 LastOR = (D->CompareOp & Dep::Or) == Dep::Or;
      }


      if (Start.IsCritical() == true)
	 if ((State & Check) != Check)
	    Dep &= ~SetMin;


      if (IsImportantDep(Start) == true &&
	  (State & Check) != Check)
	 Dep &= ~SetPolicy;
   }

   return Dep;
}
