RealPackage() const
{
   if (Nde->Pointer == 0)
      return 0;

   if ((Nde->Flags & Node::ConfFile) == Node::ConfFile)
      return Owner->PkgP + Owner->ConfP[Nde->Pointer].OwnerPkg;


   if ((Nde->Flags & Node::Diversion) == Node::Diversion)
      return 0;

   return Owner->PkgP + Nde->Pointer;
}
