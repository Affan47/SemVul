CrosshairButton()
{
  int i;

  if(!crosshair_1.active)
  {
    for(i=0; i<mainwindow->signalcomps; i++)
    {
      mainwindow->signalcomp[i]->hascursor1 = 0;
      mainwindow->signalcomp[i]->hascursor2 = 0;
    }
    crosshair_1.value = 0.0;
    crosshair_2.value = 0.0;
    mainwindow->signalcomp[signal_nr]->hascursor1 = 1;
    use_move_events = 0;
    setMouseTracking(TRUE);
    crosshair_1.active = 1;
    crosshair_2.active = 0;
    crosshair_1.moving = 0;
    crosshair_2.moving = 0;
    crosshair_1.file_num = mainwindow->signalcomp[signal_nr]->filenum;

    crosshair_1.x_position = w * 0.3;
    crosshair_1.y_position = h * 0.7;

    drawCurve_stage_1();
  }
  else
  {
    if(!crosshair_2.active)
    {
      for(i=0; i<mainwindow->signalcomps; i++)
      {
        mainwindow->signalcomp[i]->hascursor2 = 0;
      }
      crosshair_2.value = 0.0;
      mainwindow->signalcomp[signal_nr]->hascursor2 = 1;
      use_move_events = 0;
      setMouseTracking(TRUE);
      crosshair_2.active = 1;
      crosshair_1.moving = 0;
      crosshair_2.moving = 0;
      crosshair_2.file_num = mainwindow->signalcomp[signal_nr]->filenum;

      crosshair_2.x_position = w * 0.3;
      crosshair_2.y_position = h * 0.7;

      drawCurve_stage_1();
    }
  }

  sidemenu->close();
}
