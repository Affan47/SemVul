buttonColor(ButtonFlag flag_, unsigned long color_)
{
  if (color_ != buttonColor(flag_))
   {
     switch(flag_)
      {
      case ComboButton:
        if(_comboArrow != 0) _comboArrow->color(color_);
        break;

      case UpDownArrows:
        if(_upArrow != 0) _upArrow->color(color_);
        if(_downArrow != 0) _downArrow->color(color_);
        break;

      case TextButton:
      default:
        break;

      }
     redraw();
   }
}
