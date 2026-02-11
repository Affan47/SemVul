SetEventListener(Handle<Object> callback,
                                Handle<Object> data) {
  HandleScope scope(isolate_);
  GlobalHandles* global_handles = isolate_->global_handles();


  if (!event_listener_.is_null()) {
    global_handles->Destroy(
        reinterpret_cast<Object**>(event_listener_.location()));
    event_listener_ = Handle<Object>();
  }
  if (!event_listener_data_.is_null()) {
    global_handles->Destroy(
        reinterpret_cast<Object**>(event_listener_data_.location()));
    event_listener_data_ = Handle<Object>();
  }


  if (!callback->IsUndefined() && !callback->IsNull()) {
    event_listener_ = Handle<Object>::cast(
        global_handles->Create(*callback));
    if (data.is_null()) {
      data = isolate_->factory()->undefined_value();
    }
    event_listener_data_ = Handle<Object>::cast(
        global_handles->Create(*data));
  }

  ListenersChanged();
}
