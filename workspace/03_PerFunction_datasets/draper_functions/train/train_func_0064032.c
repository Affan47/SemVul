DeleteInterest(LInterest *interest)
{
  if (interest) {
    if (interest->filter) LListFree(interest->filter);
    OOGLFree(interest);
  }
}
