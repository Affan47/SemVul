getDescription() const
{
   ASCString res = "Consume " + toGet.toString() + " resources ";
   const ContainerBase* c = getContainer();
   if ( c )
      res += " of  " + c->getName();
   return  res;
}
