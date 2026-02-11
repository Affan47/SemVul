create()
{
    QBoxLayout *layout=new QBoxLayout(QBoxLayout::TopToBottom, this);
    layout->addWidget(mw);
    layout->addWidget(buttonBox);
    connect(buttonBox, SIGNAL(clicked(QAbstractButton *)), this, SLOT(buttonPressed(QAbstractButton *)));
}
