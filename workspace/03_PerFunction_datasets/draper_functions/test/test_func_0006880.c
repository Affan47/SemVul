seek(int64_t p, int whence) {
  if (whence==SEEK_SET) off=p;
  else if (whence==SEEK_CUR) off+=p;
  else if (whence==SEEK_END) off=(files.size() ? files.back().end : 0)+p;
  else assert(false);
  if (mode=='r') {
    int oldfi=fi;
    for (fi=0; fi<size(files) && off>=files[fi].end; ++fi);
    if (fi!=oldfi) {
      in.close();
      if (fi<size(files) && !in.open(files[fi].fn.c_str(), aes,
          fi>0 ? files[fi-1].end : 0))
        error("cannot reopen archive after seek");
    }
    if (fi<size(files)) in.seek(off-files[fi].end, SEEK_END);
  }
  else if (mode=='w') {
    assert(files.size()>0);
    assert(out.isopen());
    assert(fi+1==size(files));
    p=off;
    if (files.size()>=2) p-=files[files.size()-2].end;
    if (p<0) error("seek before start of output");
    out.seek(p, SEEK_SET);
  }
}
