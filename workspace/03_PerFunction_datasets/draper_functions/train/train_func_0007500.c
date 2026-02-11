menu_draw_pal(MENU_ITEM *self,int menu_pos)
{
  SDL_Rect b;
  int i;
  int pal=(int)self->user_data;

  b.x=100;
  b.y=MENUY+menu_pos*hl+3;
  b.w=22;
  b.h=7;
  SDL_FillRect(back,&b,COL32_TO_16(0x000000));

  b.w=5;
  b.h=5;
  b.y+=1;
  for(i=0;i<4;i++) {
    b.x=101+i*5;

    SDL_FillRect(back,&b,COL32_TO_16(conf.pal[pal][3-i]));
  }

}
