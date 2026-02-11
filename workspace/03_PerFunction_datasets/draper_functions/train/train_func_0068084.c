Resize(unsigned long long const newSize)
{
   unsigned long long const EndSize = d->End - d->Start;


   char* newBuffer = (char*)realloc(d->Buffer, sizeof(char) * newSize);
   if (newBuffer == NULL)
      return false;
   d->Buffer = newBuffer;
   d->Size = newSize;


   d->Start = d->Buffer;
   d->End = d->Start + EndSize;
   return true;
}
