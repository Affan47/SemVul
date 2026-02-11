CodeDeleteEvent(Address from) {
  if (!log_->IsEnabled()) return;
  if (FLAG_ll_prof) LowLevelCodeDeleteEvent(from);
  if (Serializer::enabled() && address_to_name_map_ != NULL) {
    address_to_name_map_->Remove(from);
  }
  DeleteEventInternal(CODE_DELETE_EVENT, from);
}
