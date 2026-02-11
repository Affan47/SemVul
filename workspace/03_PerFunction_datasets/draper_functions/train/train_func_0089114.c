stopMatchAnimation()
{
    for (short Pos = 0; Pos < matchCount; Pos++) {
      hilightTile(Game->getFromPosTable(Pos), false);
    }

    TimerState = Stop;
    matchCount = 0;
}
