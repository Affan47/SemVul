Clone()
{
   NeedSeek();
   FileCopyPeerFDStream *peer=new FileCopyPeerFDStream(stream,mode);
   peer->NeedSeek();
   peer->SetBase(0);
   return peer;
}
