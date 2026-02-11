gtk_plot_ticks_transform(GtkPlotAxis *axis, gdouble x)
{
  gdouble position = 0;
  GtkPlotTicks *_ticks = &axis->ticks;
  GtkPlotTicks ticks = *_ticks;

  switch( ticks.scale ){
    case GTK_PLOT_SCALE_LOG10:
      if( x <= 0.0 || ticks.min <= 0.0 || ticks.max <= 0.0 )
        return 0;

      if(ticks.apply_break){
        if(x <= ticks.break_min) {
          position = log(x/ticks.min) / log(ticks.break_min / ticks.min);
          position *= ticks.break_position;
        } else {
          if(x <= ticks.break_max) return ticks.break_position;

          if(ticks.break_scale == GTK_PLOT_SCALE_LOG10)
            position = log(x/ticks.break_max) / log(ticks.max/ticks.break_max);
          else
            position = (x - ticks.break_max) / (ticks.max - ticks.break_max);
          position = ticks.break_position + (1 - ticks.break_position) * position;
        }
      } else {
        position = log(x/ticks.min) / log(ticks.max/ticks.min);
      }
      break;

    case GTK_PLOT_SCALE_LINEAR:
    default:
      if(ticks.apply_break){
        if(x <= ticks.break_min) {
          position = (x - ticks.min) / (ticks.break_min - ticks.min);
          position *= ticks.break_position;
        } else {
          if(x <= ticks.break_max) return ticks.break_position;

          if(ticks.break_scale == GTK_PLOT_SCALE_LOG10)
            position = log(x/ticks.break_max) / log(ticks.max/ticks.break_max);
          else
            position = (x - ticks.break_max) / (ticks.max - ticks.break_max);

          position = ticks.break_position + (1 - ticks.break_position) * position;
        }


      } else {
        position = (x - ticks.min) / (ticks.max - ticks.min);
      }
      break;
  }

  return(position);
}
