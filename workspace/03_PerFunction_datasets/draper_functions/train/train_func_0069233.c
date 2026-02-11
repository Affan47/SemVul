Notify (
    const MIDISequencer *seq,
    MIDISequencerGUIEvent e
)
{
    if ( en )
    {
        fprintf ( f, "GUI EVENT: G=%d, SG=%d, ITEM=%d\n",
                  e.GetEventGroup(),
                  e.GetEventSubGroup(),
                  e.GetEventItem()
                );

        if ( e.GetEventGroup() == MIDISequencerGUIEvent::GROUP_TRANSPORT )
        {
            if (
                e.GetEventItem() == MIDISequencerGUIEvent::GROUP_TRANSPORT_BEAT
            )
            {
                fprintf ( f, "MEAS %3d BEAT %3d\n",
                          seq->GetCurrentMeasure() + 1,
                          seq->GetCurrentBeat() + 1
                        );
            }
        }

        else if ( e.GetEventGroup() == MIDISequencerGUIEvent::GROUP_CONDUCTOR )
        {
            if (
                e.GetEventItem() == MIDISequencerGUIEvent::GROUP_CONDUCTOR_TIMESIG
            )
            {
                fprintf ( f, "TIMESIG: %d/%d\n",
                          seq->GetTrackState ( 0 )->timesig_numerator,
                          seq->GetTrackState ( 0 )->timesig_denominator
                        );
            }

            if (
                e.GetEventItem() == MIDISequencerGUIEvent::GROUP_CONDUCTOR_TEMPO
            )
            {
                fprintf ( f, "TEMPO: %3.2f\n",
                          seq->GetTrackState ( 0 )->tempobpm
                        );
            }
        }
    }
}
