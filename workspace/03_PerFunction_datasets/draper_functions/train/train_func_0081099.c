FreqSpecButton()
{
  int i, j;

  for(i=0; i<MAXSPECTRUMDIALOGS; i++)
  {
    if(mainwindow->spectrumdialog[i] == NULL)
    {
      mainwindow->spectrumdialog[i] = new UI_FreqSpectrumWindow(mainwindow->signalcomp[signal_nr], mainwindow->viewbuf, mainwindow->spectrumdialog, i, mainwindow);

      break;
    }
  }

  sidemenu->close();

  if(i<MAXSPECTRUMDIALOGS)
  {
    for(j=0; j<MAXSPECTRUMDIALOGS; j++)
    {
      if(mainwindow->signalcomp[signal_nr]->spectr_dialog[j] == 0)
      {
        mainwindow->signalcomp[signal_nr]->spectr_dialog[j] = i + 1;

        break;
      }
    }

    mainwindow->spectrumdialog[i]->SpectrumDialog->move(((i % 15) * 30) + 200, ((i % 15) * 30) + 200);

    for(j=0; j<MAXSPECTRUMDIALOGS; j++)
    {
      if(mainwindow->spectrumdialog[j] != NULL)
      {
        mainwindow->spectrumdialog[j]->SpectrumDialog->raise();
      }
    }
    mainwindow->spectrumdialog[i]->SpectrumDialog->activateWindow();
    mainwindow->spectrumdialog[i]->SpectrumDialog->raise();
  }
}
