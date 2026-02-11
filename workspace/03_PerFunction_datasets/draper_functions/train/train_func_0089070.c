receiveString(const StringMsg *msg)
{
    if (msg->equalsName("param_changed")) {
        std::string param = msg->getValue();
        if ("volume_sound" == param) {
            int volume = OptionAgent::agent()->getAsInt("volume_sound");
            setSoundVolume(volume);
        }
        else if ("volume_music" == param) {
            int volume = OptionAgent::agent()->getAsInt("volume_music");
            setMusicVolume(volume);
        }
    }
    else {
        throw UnknownMsgException(msg);
    }
}
