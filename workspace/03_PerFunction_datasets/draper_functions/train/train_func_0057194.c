CheckSizes(Header &Against) const
{
   if (HeaderSz == Against.HeaderSz &&
       NodeSz == Against.NodeSz &&
       DirSz == Against.DirSz &&
       DiversionSz == Against.DiversionSz &&
       PackageSz == Against.PackageSz &&
       ConfFileSz == Against.ConfFileSz)
            return true;
      return false;
}
