initDialog(const QString &text,const QString &urlName)
{
    q->setDefaultButton(KDialog::Ok);
    QWidget *plainPage = q->mainWidget();
   QVBoxLayout * topLayout = new QVBoxLayout( plainPage );
   topLayout->setMargin( 0 );

    QLabel * label = new QLabel( text , plainPage );
    topLayout->addWidget( label );

    urlRequester = new KUrlRequester(urlName, plainPage);
    urlRequester->setMinimumWidth(urlRequester->sizeHint().width() * 3);
    topLayout->addWidget(urlRequester);
    urlRequester->setFocus();
    QObject::connect(urlRequester->lineEdit(), SIGNAL(textChanged(QString)),
                     q, SLOT(_k_slotTextChanged(QString)));
    bool state = !urlName.isEmpty();
    q->enableButtonOk(state);
    q->enableButton(KDialog::User1, state);


    QObject::connect(q, SIGNAL(user1Clicked()), q, SLOT(_k_slotClear()));
}
