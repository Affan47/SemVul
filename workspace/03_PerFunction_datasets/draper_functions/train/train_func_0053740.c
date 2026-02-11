BgColorButtonClicked(SpecialButton *)
{
  int i;

  QColor temp;

  QPalette palette;

  temp = QColorDialog::getColor(mainwindow->maincurve->backgroundcolor, tab1);

  if(temp.isValid())
  {
    mainwindow->maincurve->backgroundcolor = temp;

    BgColorButton->setColor(mainwindow->maincurve->backgroundcolor);

    palette.setColor(QPalette::Text, mainwindow->maincurve->text_color);
    palette.setColor(QPalette::Base, mainwindow->maincurve->backgroundcolor);

    for(i=0; i<mainwindow->files_open; i++)
    {
      if(mainwindow->annotations_dock[i])
      {
        mainwindow->annotations_dock[i]->list->setPalette(palette);
      }
    }

    mainwindow->maincurve->update();
  }
}
