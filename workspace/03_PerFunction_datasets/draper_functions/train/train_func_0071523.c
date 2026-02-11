TourneyInit (void)
{
  NextOpponent = 2;
  LastOpponent = 0;
  TourneyReadIni ();
  if (use_tourney->value)
    gi.dprintf ("Tourney mode enabled.\n");
}
