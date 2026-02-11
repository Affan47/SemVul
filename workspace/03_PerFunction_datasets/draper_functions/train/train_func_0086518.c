startLink(const Address &addr)
{
  start();
  if (linkDepth_++ == 0) {
    if (inlineState_ == inlineMiddle)
      doStartLink(addr);
    else {
      pendingLink_ = addr;
      havePendingLink_ = 1;
    }
  }
}
