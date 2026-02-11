ReadAlgorithmIdentifier(uint8** pos, uint8* end) {
  if(!(*pos + sizeof(kRsaAlgorithmIdentifier) < end)) return false;
  if(!(memcmp(*pos, kRsaAlgorithmIdentifier,
                     sizeof(kRsaAlgorithmIdentifier)) == 0)) return false;
  (*pos) += sizeof(kRsaAlgorithmIdentifier);
  return true;
}
