about() {
    QMessageBox aboutBox;
    aboutBox.setIconPixmap(QPixmap(":/images/kdocker.png"));
    aboutBox.setWindowTitle(tr("About %1 - %2").arg(qApp->applicationName()).arg(qApp->applicationVersion()));
    aboutBox.setText(Constants::ABOUT_MESSAGE);
    aboutBox.setInformativeText(tr("See %1 for more information.").arg("<a href=\"https://launchpad.net/kdocker\">https://launchpad.net/kdocker</a>"));
    aboutBox.setStandardButtons(QMessageBox::Ok);
    aboutBox.exec();
}
