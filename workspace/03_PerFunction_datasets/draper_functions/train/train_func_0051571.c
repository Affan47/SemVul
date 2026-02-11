EnqueueDebugCommand(v8::Debug::ClientData* client_data) {
  CommandMessage message = CommandMessage::New(Vector<uint16_t>(), client_data);
  event_command_queue_.Put(message);


  if (!Debug::InDebugger()) {
    StackGuard::DebugCommand();
  }
}
