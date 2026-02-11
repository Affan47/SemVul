executeActions(MovieClip* m, DisplayList& ) const
{

    sound::sound_handler* handler =
        getRunResources(*getObject(m)).soundHandler();

#ifdef USE_SOUND
    if (handler) {
        if (_soundInfo.stopPlayback) {

            handler->stopEventSound(m_handler_id);
        }
        else {

            const sound::SoundEnvelopes* env =
                _soundInfo.envelopes.empty() ? 0 : &_soundInfo.envelopes;

            handler->startSound(m_handler_id,
                    _soundInfo.loopCount,
                    env,
                    !_soundInfo.noMultiple,
                    _soundInfo.inPoint,
                    _soundInfo.outPoint
                );
        }
    }
#endif
}
