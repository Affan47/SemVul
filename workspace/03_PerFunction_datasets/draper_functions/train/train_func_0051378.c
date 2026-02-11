setupUi()
    {
        ui->setupUi(q);
        ui->nss->setValidator(new QRegExpValidator(QRegExp("^[1-2]\\d{0,5}[0-9AB]\\d{0,6}$")));
        ui->nss->setInputMask("0 00 00 0N 000 000");
        ui->nss->setMaximumWidth(ui->nss->fontMetrics().width(QString().fill('9', 18)));


        ui->key->setFocusPolicy(Qt::NoFocus);
        ui->key->setReadOnly(true);
        ui->key->setMaximumWidth(ui->key->fontMetrics().width(QString().fill('9', 4)));


    }
