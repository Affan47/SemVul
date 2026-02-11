freqbox2valuechanged(double value)
{
  int j;

  if(freq1box->value() > (value * 0.9))
  {
    QObject::disconnect(freq1box, SIGNAL(valueChanged(double)), this, SLOT(freqbox1valuechanged(double)));

    freq1box->setValue(value * 0.9);

    QObject::connect(freq1box, SIGNAL(valueChanged(double)), this, SLOT(freqbox1valuechanged(double)));
  }

  for(j=0; j<10; j++)  qApp->processEvents();

  update_filter();
}
