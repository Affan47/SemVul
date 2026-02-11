setupPrograms() {
  while (_lastProcessed != _soundsPlaying) {
    uint8 *ptr = getProgram(_soundIdTable[_lastProcessed]);
    uint8 chan = *ptr++;
    uint8 priority = *ptr++;


    Channel &channel = _channels[chan];

    if (priority >= channel.priority) {
      initChannel(channel);
      channel.priority = priority;
      channel.dataptr = ptr;
      channel.tempo = 0xFF;
      channel.position = 0xFF;
      channel.duration = 1;
      unkOutput2(chan);
    }

    ++_lastProcessed;
    _lastProcessed &= 0x0F;
  }
}
