startBox(const BoxNIC &nic)
{
  flushPendingElements();
  os() << "<box";
  if (nic.isDisplay) {
    os() << " display=" << quot << trueString << quot;
    displayNIC(nic);
  }
  else
    inlineNIC(nic);
  outputIcs();
  os() << '>' << RE;
}
