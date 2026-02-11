BuildStatsObject(NODE_STAT_STRUCT *s) {
  HandleScope scope;

  if (dev_symbol.IsEmpty()) {
    dev_symbol = NODE_PSYMBOL("dev");
    ino_symbol = NODE_PSYMBOL("ino");
    mode_symbol = NODE_PSYMBOL("mode");
    nlink_symbol = NODE_PSYMBOL("nlink");
    uid_symbol = NODE_PSYMBOL("uid");
    gid_symbol = NODE_PSYMBOL("gid");
    rdev_symbol = NODE_PSYMBOL("rdev");
    size_symbol = NODE_PSYMBOL("size");
    blksize_symbol = NODE_PSYMBOL("blksize");
    blocks_symbol = NODE_PSYMBOL("blocks");
    atime_symbol = NODE_PSYMBOL("atime");
    mtime_symbol = NODE_PSYMBOL("mtime");
    ctime_symbol = NODE_PSYMBOL("ctime");
  }

  Local<Object> stats =
    stats_constructor_template->GetFunction()->NewInstance();


  stats->Set(dev_symbol, Integer::New(s->st_dev));


  stats->Set(ino_symbol, Integer::New(s->st_ino));


  stats->Set(mode_symbol, Integer::New(s->st_mode));


  stats->Set(nlink_symbol, Integer::New(s->st_nlink));


  stats->Set(uid_symbol, Integer::New(s->st_uid));


  stats->Set(gid_symbol, Integer::New(s->st_gid));


  stats->Set(rdev_symbol, Integer::New(s->st_rdev));


  stats->Set(size_symbol, Number::New(s->st_size));

#ifdef __POSIX__

  stats->Set(blksize_symbol, Integer::New(s->st_blksize));


  stats->Set(blocks_symbol, Integer::New(s->st_blocks));
#endif


  stats->Set(atime_symbol, NODE_UNIXTIME_V8(s->st_atime));


  stats->Set(mtime_symbol, NODE_UNIXTIME_V8(s->st_mtime));


  stats->Set(ctime_symbol, NODE_UNIXTIME_V8(s->st_ctime));

  return scope.Close(stats);
}
