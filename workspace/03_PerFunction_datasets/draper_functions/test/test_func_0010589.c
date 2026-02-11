accept()
{
    ConfigPage* p;
    QString errorMsg, errorItem;
    foreach(p, _pages)
        if (!p->check(errorMsg, errorItem)) {
            if (!errorMsg.isEmpty()) {
                errorMsg = QString("<font color=red>%1</color>").arg(errorMsg);
                _errorLabel->setText(errorMsg);
                _clearTimer.start(5000);
            }
            activate(QString("%1/%2").arg(p->title(), errorItem));
	    return;
	}

    foreach(p, _pages)
	p->accept();

    QDialog::accept();
}
