slotSettingsPointMatch()
{
  slotStatusNormalMsg(QString(tr("Configuring point match settings...")));

  DigitDoc* doc = activeDocument();
  if (doc)
  {
    PointMatchSettings match = doc->pointMatchSettings();
    PointMatchDlg* dlg = new PointMatchDlg(doc->title(),
      doc->curveStyle(curveCmb->currentText()), &match);
    CHECK_PTR_ENGAUGE(dlg);

    if (dlg->exec() == QDialog::Accepted)
    {
      DefaultSettings::instance().setPointMatchSettings(match);
      doc->setPointMatchSettings(match);
    }

    delete dlg;
  }

  slotStatusNormalMsg(QString(tr("Ready.")));
}
