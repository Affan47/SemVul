removeUnsupportedProperties(const StringList &properties)
{


  if(dynamic_cast<APE::File* >(this))
    dynamic_cast<APE::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<FLAC::File* >(this))
    dynamic_cast<FLAC::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<MPC::File* >(this))
    dynamic_cast<MPC::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<MPEG::File* >(this))
    dynamic_cast<MPEG::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<Ogg::FLAC::File* >(this))
    dynamic_cast<Ogg::FLAC::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<Ogg::Speex::File* >(this))
    dynamic_cast<Ogg::Speex::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<Ogg::Vorbis::File* >(this))
    dynamic_cast<Ogg::Vorbis::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<RIFF::AIFF::File* >(this))
    dynamic_cast<RIFF::AIFF::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<RIFF::WAV::File* >(this))
    dynamic_cast<RIFF::WAV::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<S3M::File* >(this))
    dynamic_cast<S3M::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<TrueAudio::File* >(this))
    dynamic_cast<TrueAudio::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<WavPack::File* >(this))
    dynamic_cast<WavPack::File* >(this)->removeUnsupportedProperties(properties);
  else if(dynamic_cast<XM::File* >(this))
    dynamic_cast<XM::File* >(this)->removeUnsupportedProperties(properties);
  else
    tag()->removeUnsupportedProperties(properties);
}
