SetCandidateRelease(pkgCache::VerIterator TargetVer,
					std::string const &TargetRel)
{
   std::list<std::pair<pkgCache::VerIterator, pkgCache::VerIterator> > Changed;
   return SetCandidateRelease(TargetVer, TargetRel, Changed);
}
