MIDI_RerouteMidiChannel
   (
   int channel,
   int ( *function )( int event, int c1, int c2 )
   )

   {
   if ( ( channel >= 1 ) && ( channel <= 16 ) )
      {
      _MIDI_RerouteFunctions[ channel - 1 ] = function;
      }
   }
