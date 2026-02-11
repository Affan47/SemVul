ToggleAutoNewFrame() {
  _autonewframe = !_autonewframe;
  if (_autonewframe_tts) _autonewframe_tts->set(TelltaleState::is_chosen, _autonewframe);
}
