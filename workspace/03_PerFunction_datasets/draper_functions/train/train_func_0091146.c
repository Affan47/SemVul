stack_at(int i)
{
 if (i < 0 || i > items.size()) {
  debugmsg("Attempted to access stack %d in an inventory (size %d)",
           i, items.size());
  return nullstack;
 }
 return items[i];
}
