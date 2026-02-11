LeaveMuc(const std::string& room) {
  buzz::Jid room_jid;
  const buzz::Jid* muc_jid = FirstMucJid();
  if (room.length() > 0) {
    room_jid = buzz::Jid(room);
  } else if (mucs_.size() > 0) {

    if (muc_jid) {
      room_jid = *(muc_jid);
    }
  }

  if (!room_jid.IsValid()) {
    console_->PrintLine("Invalid MUC JID.");
    return;
  }

  MucMap::iterator elem = mucs_.find(room_jid);
  if (elem == mucs_.end()) {
    console_->PrintLine("No such MUC.");
    return;
  }

  buzz::Muc* muc = elem->second;
  muc->set_state(buzz::Muc::MUC_LEAVING);

  buzz::Status status;
  status.set_jid(my_status_.jid());
  status.set_available(false);
  status.set_priority(0);
  presence_out_->SendDirected(muc->local_jid(), status);
}
