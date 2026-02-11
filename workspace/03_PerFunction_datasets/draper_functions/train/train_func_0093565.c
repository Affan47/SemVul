mouseEvent(const event_id& event)
{
    if (unloaded()) {

        return;
    }

    MouseState new_state = _mouseState;


    switch (event.id())
    {
        case event_id::ROLL_OUT:
        case event_id::RELEASE_OUTSIDE:
            new_state = MOUSESTATE_UP;
            break;

        case event_id::RELEASE:
        case event_id::ROLL_OVER:
        case event_id::DRAG_OUT:
        case event_id::MOUSE_UP:
            new_state = MOUSESTATE_OVER;
            break;

        case event_id::PRESS:
        case event_id::DRAG_OVER:
        case event_id::MOUSE_DOWN:
            new_state = MOUSESTATE_DOWN;
            break;

        default:

            log_error(_("Unhandled button event %s"), event);
            break;
    }

    set_current_state(new_state);


    do {

        if (!_def->hasSound()) break;


        sound::sound_handler* s = getRunResources(*getObject(this)).soundHandler();
        if (!s) break;

        int bi;

        switch (event.id())
        {
            case event_id::ROLL_OUT:
                bi = 0;
                break;
            case event_id::ROLL_OVER:
                bi = 1;
                break;
            case event_id::PRESS:
                bi = 2;
                break;
            case event_id::RELEASE:
                bi = 3;
                break;
            default:
                bi = -1;
                break;
        }


        if (bi < 0) break;
#ifdef USE_SOUND
        const SWF::DefineButtonSoundTag::ButtonSound& bs =
            _def->buttonSound(bi);


        if (!bs.soundID) break;


        if (!bs.sample) break;

        if (bs.soundInfo.stopPlayback) {
            s->stopEventSound(bs.sample->m_sound_handler_id);
        }
        else {
            const SWF::SoundInfoRecord& sinfo = bs.soundInfo;

            const sound::SoundEnvelopes* env =
                sinfo.envelopes.empty() ? 0 : &sinfo.envelopes;

            s->startSound(bs.sample->m_sound_handler_id,
                    bs.soundInfo.loopCount,
                    env,
                    !sinfo.noMultiple,
                    sinfo.inPoint,
                    sinfo.outPoint
                    );
        }
#endif

    } while(0);


    movie_root& mr = stage();

    ButtonActionPusher xec(mr, this);
    _def->forEachTrigger(event, xec);


    std::auto_ptr<ExecutableCode> code (get_event_handler(event));
    if (code.get()) {
        mr.pushAction(code, movie_root::PRIORITY_DOACTION);
    }

    sendEvent(*getObject(this), get_environment(), event.functionURI());
}
