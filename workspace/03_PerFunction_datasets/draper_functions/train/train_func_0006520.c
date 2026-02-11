filtermodelboxvaluechanged(int model)
{
  int type;


  QObject::disconnect(orderbox, SIGNAL(valueChanged(int)),        this, SLOT(orderboxvaluechanged(int)));
  QObject::disconnect(modelbox, SIGNAL(currentIndexChanged(int)), this, SLOT(filtermodelboxvaluechanged(int)));

  type = typebox->currentIndex();

  last_model = model;

  freqboxlabel->setText("Frequency");
  freqbox->setVisible(TRUE);

  if(type != 2)
  {
    orderboxlabel->setText("Order");
    if((type == 3) || (type == 4))
    {
      orderbox->setMaximum(16);
    }
    else
    {
      orderbox->setMaximum(8);
    }
    orderbox->setSingleStep(1);
    orderbox->setMinimum(1);
    orderbox->setValue(last_order);

    if(model == 0)
    {
      ripplebox->setVisible(FALSE);
      ordervaluelabel->setVisible(TRUE);
      orderlabel->setText("Slope roll-off:");
      ordervaluelabel->setText(QString::number(6 * orderbox->value(), 'f', 0).append(" dB / octave"));
    }

    if(model == 1)
    {
      orderlabel->setText("passband ripple");
      ordervaluelabel->setVisible(FALSE);
      ripplebox->setVisible(TRUE);
    }

    if(model == 2)
    {
      ripplebox->setVisible(FALSE);
      ordervaluelabel->setVisible(TRUE);
      orderlabel->setText("");
      ordervaluelabel->setText("");
    }

    if(model == 3)
    {
      orderlabel->setText("");
      ordervaluelabel->setText("");
      freqboxlabel->setText("");
      freqbox2label->setText("");
      freqbox->setVisible(FALSE);
      ripplebox->setVisible(FALSE);
      ordervaluelabel->setVisible(FALSE);
      orderlabel->setText("");
      ordervaluelabel->setText("");
      orderboxlabel->setText("Samples");
      orderbox->setMaximum(10000);
      orderbox->setSingleStep(1);
      orderbox->setMinimum(2);
      orderbox->setValue(last_samples);
    }
  }

  updatecurve();

  QObject::connect(orderbox, SIGNAL(valueChanged(int)),        this, SLOT(orderboxvaluechanged(int)));
  QObject::connect(modelbox, SIGNAL(currentIndexChanged(int)), this, SLOT(filtermodelboxvaluechanged(int)));
}
