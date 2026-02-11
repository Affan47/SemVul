HandleStanza(const XmlElement* stanza) {


  const XmlElement* xstanza;
  const XmlElement* invite;
  if (stanza->Name() != QN_MESSAGE) return false;
  xstanza = stanza->FirstNamed(QN_MUC_USER_X);
  if (!xstanza) return false;
  invite = xstanza->FirstNamed(QN_MUC_USER_INVITE);
  if (!invite) return false;


  std::vector<AvailableMediaEntry> v;
  const XmlElement* avail =
    invite->FirstNamed(QN_GOOGLE_MUC_USER_AVAILABLE_MEDIA);
  if (avail) {
    for (const XmlElement* entry = avail->FirstNamed(QN_GOOGLE_MUC_USER_ENTRY);
        entry;
        entry = entry->NextNamed(QN_GOOGLE_MUC_USER_ENTRY)) {
      AvailableMediaEntry tmp;


      tmp.label = atoi(entry->Attr(QN_LABEL).c_str());
      tmp.type = static_cast<AvailableMediaEntry::type_t>(
          bodytext_to_array_pos(
              entry->FirstNamed(QN_GOOGLE_MUC_USER_TYPE),
              types,
              sizeof(types)/sizeof(const char*),
              AvailableMediaEntry::TYPE_UNKNOWN));
      tmp.status = static_cast<AvailableMediaEntry::status_t>(
          bodytext_to_array_pos(
              entry->FirstNamed(QN_GOOGLE_MUC_USER_STATUS),
              statuses,
              sizeof(statuses)/sizeof(const char*),
              AvailableMediaEntry::STATUS_UNKNOWN));
      v.push_back(tmp);
    }
  }
  SignalInviteReceived(Jid(invite->Attr(QN_FROM)), Jid(stanza->Attr(QN_FROM)),
      v);
  return true;
}
