expandCapacity(int requiredLength)
{
  Rep* r = m_rep->baseString;

  if (requiredLength > r->capacity) {
    size_t newCapacity = expandedSize(requiredLength, r->preCapacity);
    UChar* oldBuf = r->buf;
    r->buf = reallocChars(r->buf, newCapacity);
    if (!r->buf) {
        r->buf = oldBuf;
        m_rep = &Rep::null;
        return;
    }
    r->capacity = newCapacity - r->preCapacity;
  }
  if (requiredLength > r->usedCapacity) {
    r->usedCapacity = requiredLength;
  }
}
