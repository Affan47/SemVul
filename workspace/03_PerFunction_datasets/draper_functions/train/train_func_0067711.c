BareJid() const {
  if (!IsValid())
    return Jid();
  if (!IsFull())
    return *this;
  return Jid(node_name_, domain_name_, STR_EMPTY);
}
