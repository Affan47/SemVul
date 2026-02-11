upload()
{

    token = appsettings->cvalue(mainWindow->cyclist, GC_CYCLINGANALYTICS_TOKEN, "").toString();
    if (token=="")
    {
        QMessageBox aMsgBox;
        aMsgBox.setText(tr("Cannot login to CyclingAnalytics. Check permission"));
        aMsgBox.exec();
        return;
    }


    if(cyclingAnalyticsUploadId.length()>0)
    {
        overwrite = false;

        dialog = new QDialog();
        QVBoxLayout *layout = new QVBoxLayout;

        QVBoxLayout *layoutLabel = new QVBoxLayout();
        QLabel *label = new QLabel();
        label->setText(tr("This Ride is marked as already on CyclingAnalytics. Are you sure you want to upload it?"));
        layoutLabel->addWidget(label);

        QPushButton *ok = new QPushButton(tr("OK"), dialog);
        QPushButton *cancel = new QPushButton(tr("Cancel"), dialog);
        QHBoxLayout *buttons = new QHBoxLayout();
        buttons->addStretch();
        buttons->addWidget(cancel);
        buttons->addWidget(ok);

        connect(ok, SIGNAL(clicked()), this, SLOT(okClicked()));
        connect(cancel, SIGNAL(clicked()), this, SLOT(closeClicked()));

        layout->addLayout(layoutLabel);
        layout->addLayout(buttons);

        dialog->setLayout(layout);

        if (!dialog->exec()) return;
    }

    requestUploadCyclingAnalytics();

    if(!uploadSuccessful)
    {
        parent->progressLabel->setText("Error uploading to CyclingAnalytics");
    }
    else
    {
        parent->progressLabel->setText(tr("Successfully uploaded to CyclingAnalytics"));
    }
}
