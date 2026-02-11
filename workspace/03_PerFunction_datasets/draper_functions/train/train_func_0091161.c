updateLru(DomainNode* node, time_t now)
{
  if(node->getInLru()) {
    lruTracker_.erase({node->getLruAccessTime(), node});
  } else {
    node->setInLru(true);
  }
  node->setLruAccessTime(now);
  lruTracker_.insert({node->getLruAccessTime(), node});
}
