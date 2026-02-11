OnRequestDone(talk_base::SignalThread* data) {
  talk_base::AsyncHttpRequest* request =
      static_cast<talk_base::AsyncHttpRequest*>(data);


  std::list<talk_base::AsyncHttpRequest*>::iterator it =
      std::find(requests_.begin(), requests_.end(), request);
  if (it != requests_.end()) {
    requests_.erase(it);
  }

  if (request->response().scode != 200) {
    LOG(LS_WARNING) << "HTTPPortAllocator: request "
                    << " received error " << request->response().scode;
    TryCreateRelaySession();
    return;
  }
  LOG(LS_INFO) << "HTTPPortAllocator: request succeeded";

  talk_base::MemoryStream* stream =
      static_cast<talk_base::MemoryStream*>(request->response().document.get());
  stream->Rewind();
  size_t length;
  stream->GetSize(&length);
  std::string resp = std::string(stream->GetBuffer(), length);
  ReceiveSessionResponse(resp);
}
