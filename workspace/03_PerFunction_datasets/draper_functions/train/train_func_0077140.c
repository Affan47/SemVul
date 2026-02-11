drawLine(int start_x, double start_y, int end_x, double end_y, QColor lineColor)
{
  line1Color = lineColor;

  line1_start_x = start_x;
  if(line1_start_x < 0)
  {
    line1_start_x = 0;
  }
  if(line1_start_x >= bufsize)
  {
    line1_start_x = bufsize - 1;
  }

  line1_start_y = start_y;

  line1_end_x = end_x;
  if(line1_end_x < 0)
  {
    line1_end_x = 0;
  }
  if(line1_end_x >= bufsize)
  {
    line1_end_x = bufsize - 1;
  }

  line1_end_y = end_y;

  line1Enabled = TRUE;

  update();
}
