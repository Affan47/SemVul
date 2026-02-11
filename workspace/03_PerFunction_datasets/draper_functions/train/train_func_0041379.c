SetSeq ( MIDISequencer *seq )
{
    if ( notifier )
    {
        notifier->Notify ( sequencer, MIDISequencerGUIEvent ( MIDISequencerGUIEvent::GROUP_ALL ) );
    }

    sequencer = seq;
}
