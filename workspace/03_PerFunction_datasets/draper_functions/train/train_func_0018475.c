updateSettings( void)
{
    if( Mix_FadingMusic() != MIX_NO_FADING) return;

    bool oldPlayMusic = _playMusic;
    bool oldPlayDefaultSoundtrack = _playDefaultSoundtrack;

    ConfigS::instance()->getBoolean( "playMusic", _playMusic);
    ConfigS::instance()->getBoolean(
	"playDefaultSoundtrack", _playDefaultSoundtrack);

    if( (oldPlayMusic == _playMusic) &&
	(oldPlayDefaultSoundtrack == _playDefaultSoundtrack))
    {

	return;
    }

    startMusic();
}
