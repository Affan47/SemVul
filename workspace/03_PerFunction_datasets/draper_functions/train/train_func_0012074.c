bsOpenReadStream ( FILE* stream )
{
   BitStream *bs = malloc ( sizeof(BitStream) );
   if (bs == NULL) mallocFail ( sizeof(BitStream) );
   bs->handle = stream;
   bs->buffer = 0;
   bs->buffLive = 0;
   bs->mode = 'r';
   return bs;
}
