AlignUp()
{
  for (u32 i = 0; i < numFrames; ++i)
  {
    frames[i]->Pos((s32)frames[i]->X(), 0);
  }
}
