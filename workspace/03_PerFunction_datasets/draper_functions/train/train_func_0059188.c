insertChar(Char ch)
{
  if (start() > buf_) {
    if (cur() > start())
      memmove((Char *)start() - 1, start(), (cur() - start())*sizeof(Char));
    moveLeft();
    *(Char *)cur() = ch;
  }
  else {

    if (buf_ + (bufSize_ - (nLeftOver_ + sizeof(Char) - 1)/sizeof(Char))
	== bufLim_) {
      if (bufSize_ == size_t(-1))
	abort();
      reallocateBuffer(bufSize_ + 1);
    }
    else if (nLeftOver_ > 0 && ((char *)(bufLim_ + 1) > leftOver_)) {
      char *s = (char *)(buf_ + bufSize_) - nLeftOver_;
      memmove(s, leftOver_, nLeftOver_);
      leftOver_ = s;
    }
    if (cur() < bufLim_)
      memmove((Char *)cur() + 1, cur(), (bufLim_ - cur())*sizeof(Char));
    *(Char *)cur() = ch;
    advanceEnd(end() + 1);
    bufLim_ += 1;
  }
}
