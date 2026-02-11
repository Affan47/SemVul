driver() const
{
    QString driver = fakeDevice()->property("driver").toString();

    if (driver == "alsa")
    {
        return Solid::AudioInterface::Alsa;
    }
    else if (driver == "oss")
    {
        return Solid::AudioInterface::OpenSoundSystem;
    }
    else
    {
        return Solid::AudioInterface::UnknownAudioDriver;
    }
}
