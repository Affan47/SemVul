FCEUI_SetRenderDisable(int sprites, int bg)
{

 if(sprites >= 0)
 {
  if(sprites == 2) rendis ^= 1;
  else rendis = (rendis &~1) | sprites?1:0;
 }
 if(bg >= 0)
 {
  if(bg == 2) rendis ^= 2;
  else rendis = (rendis &~2) | bg?2:0;
 }
}
