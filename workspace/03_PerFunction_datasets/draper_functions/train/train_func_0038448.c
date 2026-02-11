deviceType() const
{
    Solid::AudioInterface::AudioInterfaceTypes result;

    QStringList type_list = fakeDevice()->property("type").toString().split(',');

    foreach (const QString &type_str, type_list)
    {
        if (type_str == "control")
        {
            result|=Solid::AudioInterface::AudioControl;
        }
        else if (type_str == "input")
        {
            result|=Solid::AudioInterface::AudioInput;
        }
        else if (type_str == "output")
        {
            result|=Solid::AudioInterface::AudioOutput;
        }
    }

    return result;
}
