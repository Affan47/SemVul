getAudio(AudioPacket* audioData) {
    dynamic_cast<ComponentAudio*>(connectedDevice(IN0))->getAudio(audioData);
}
