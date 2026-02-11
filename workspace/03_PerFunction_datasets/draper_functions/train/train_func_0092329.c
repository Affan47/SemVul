toggleActions()
{
  ASSERT_ENGAUGE(comboLineSize != 0);
  comboLineSize->setCurrentText(PointSetStyles::instance().lineSizeName(settings->lineSize));
  ASSERT_ENGAUGE(comboLineColor != 0);
  comboLineColor->setCurrentText(PointSetStyles::instance().colorName(settings->lineColor));

  ASSERT_ENGAUGE(buttonOk != 0);
  buttonOk->setEnabled(validateSettings());
}
