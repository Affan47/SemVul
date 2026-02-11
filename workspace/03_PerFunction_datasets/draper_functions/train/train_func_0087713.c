unregister_client(MIDI_IO* mobject)
{
  for(unsigned int n = 0; n < clients_rep.size(); n++) {
    if (clients_rep[n] == mobject) {
      clients_rep[n] = 0;
      break;
    }
  }
}
