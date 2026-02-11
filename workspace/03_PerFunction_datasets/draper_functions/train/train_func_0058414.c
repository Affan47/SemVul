Display_effect_state(short x, short y, char * label, byte state)
{
  Block(Window_pos_X+(x*Menu_factor_X),Window_pos_Y+(y*Menu_factor_Y),
        12*Menu_factor_X,Menu_factor_Y<<3,MC_Light);

  Print_in_window(x,y,label,(state)?MC_White:MC_Black,MC_Light);
  if (state)
    Print_in_window(x+56,y,":ON ",MC_White,MC_Light);
  else
    Print_in_window(x+56,y,":OFF",MC_Black,MC_Light);
}
