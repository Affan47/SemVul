close_all_files()
{
  int i, j, k,
      button_nr=0;


  live_stream_active = 0;
  live_stream_timer->stop();
  toolsmenu->setEnabled(TRUE);
  timemenu->setEnabled(TRUE);
  windowmenu->setEnabled(TRUE);
  former_page_Act->setEnabled(TRUE);
  shift_page_left_Act->setEnabled(TRUE);
  shift_page_right_Act->setEnabled(TRUE);
  next_page_Act->setEnabled(TRUE);
  shift_page_up_Act->setEnabled(TRUE);
  shift_page_down_Act->setEnabled(TRUE);
  printmenu->setEnabled(TRUE);
  recent_filesmenu->setEnabled(TRUE);

  if(annotations_edited)
  {
    QMessageBox messagewindow;
    messagewindow.setText("There are unsaved annotations,\n are you sure you want to close this file?");
    messagewindow.setIcon(QMessageBox::Question);
    messagewindow.setStandardButtons(QMessageBox::Cancel | QMessageBox::Close);
    messagewindow.setDefaultButton(QMessageBox::Cancel);
    button_nr = messagewindow.exec();
  }

  if(button_nr == QMessageBox::Cancel)
  {
    return;
  }

  annotations_edited = 0;

#ifdef BK_MRS_project


  if(bk_mrs_project_file != NULL)
  {
    fclose(bk_mrs_project_file);
    bk_mrs_project_file = NULL;
  }

#endif

  remove_all_signals();

  while(files_open)
  {
    files_open--;
    if(edfheaderlist[files_open]->file_hdl != NULL)
    {
      fclose(edfheaderlist[files_open]->file_hdl);
    }
    free(edfheaderlist[files_open]->edfparam);
    free(edfheaderlist[files_open]);
    edfplus_annotation_delete_list(&annotationlist[files_open]);

    if(annotations_dock[files_open] != NULL)
    {
      annotations_dock[files_open]->docklist->close();
      delete annotations_dock[files_open];
      annotations_dock[files_open] = NULL;
    }

    delete sel_viewtime_act[files_open];
  }

  edfplus_annotation_delete_list(&annotationlist_backup);

  sel_viewtime = 0;

  pagetime = 10 * TIME_DIMENSION;

  timescale_doubler = 10;

  amplitude_doubler = 10;

  for(i=0; i<64; i++)
  {
    zoomhistory->pntr = 0;
    zoomhistory->pagetime[i] = 10 * TIME_DIMENSION;
    for(j=0; j<MAXFILES; j++)
    {
      zoomhistory->viewtime[i][j] = 0;
    }
    for(j=0; j<MAXSIGNALS; j++)
    {
      zoomhistory->voltpercm[i][j] = 70;
      zoomhistory->screen_offset[i][j] = 0.0;
      for(k=0; k<MAXSIGNALS; k++)
      {
        zoomhistory->sensitivity[i][j][k] = 0.0475;
      }
    }
  }

  annotationEditDock->dockedit->hide();

  save_act->setEnabled(FALSE);

  annotations_edited = 0;

  setWindowTitle(PROGRAM_NAME);

  if(!exit_in_progress)
  {
    maincurve->update();
  }
}
