Compare_video_modes(const void *p1, const void *p2)
{
  const T_Video_mode *mode1 = (const T_Video_mode *)p1;
  const T_Video_mode *mode2 = (const T_Video_mode *)p2;


  if(mode1->Width - mode2->Width)
    return mode1->Width - mode2->Width;


  return mode1->Height - mode2->Height;
}
