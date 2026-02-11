CreateCopyPeer(const FileAccessRef& session,const char *path,FA::open_mode mode)
{
   ParsedURL url(path,true);
   if(IsRemoteNonURL(url,mode))
      return new FileCopyPeerFA(session,path,mode);
   return CreateCopyPeer(url,path,mode);
}
