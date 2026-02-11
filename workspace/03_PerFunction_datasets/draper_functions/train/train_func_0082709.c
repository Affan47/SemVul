Mystrdup(const char *From)
{
   unsigned int Len = strlen(From) + 1;
   if (StrLeft <= Len)
   {
      StrLeft = 4096*10;
      StrPool = (char *)malloc(StrLeft);

      BigBlock *Block = new BigBlock;
      Block->Block = StrPool;
      Block->Next = BlockList;
      BlockList = Block;
   }

   memcpy(StrPool,From,Len);
   StrLeft -= Len;

   char *Res = StrPool;
   StrPool += Len;
   return Res;
}
