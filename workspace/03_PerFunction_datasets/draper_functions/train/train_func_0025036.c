operator()(const string &src, const string &dst) const
  {
    struct stat srcbuf, dstbuf;

    bool do_copy=true;

    if(lstat(src.c_str(), &srcbuf)!=0)
      {
	perror(("Can't stat "+src).c_str());
	return false;
      }

    if(lstat(dst.c_str(), &dstbuf)!=0)
      {
	if(errno!=ENOENT)
	  {
	    perror(("Can't stat "+dst).c_str());
	    return false;
	  }
      }
    else if(dstbuf.st_mtime>srcbuf.st_mtime)
      do_copy=false;

    if(do_copy)
      {
	if(!copy(src, dst))
	  {
	    perror(("Can't copy "+src+" to "+dst).c_str());
	    return false;
	  }
      }

    return true;
  }
}
