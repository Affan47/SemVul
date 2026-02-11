Button_Lines_switch_mode(void)
{
  char icon;

  if (Selected_line_mode==OPERATION_LINE)
    Selected_line_mode=OPERATION_K_LINE;
  else
  {
    if (Selected_line_mode==OPERATION_K_LINE)
      Selected_line_mode=OPERATION_CENTERED_LINES;
    else
      Selected_line_mode=OPERATION_LINE;
  }
  switch(Selected_line_mode)
  {
    default:
    case OPERATION_LINE:
      icon=-1;
      break;
    case OPERATION_K_LINE:
      icon=MENU_SPRITE_K_LINE;
      break;
    case OPERATION_CENTERED_LINES:
      icon=MENU_SPRITE_CENTERED_LINES;
      break;
  }

  Hide_cursor();
  Display_sprite_in_menu(BUTTON_LINES,icon);
  Draw_menu_button(BUTTON_LINES,BUTTON_PRESSED);
  Start_operation_stack(Selected_line_mode);
  Display_cursor();
}
