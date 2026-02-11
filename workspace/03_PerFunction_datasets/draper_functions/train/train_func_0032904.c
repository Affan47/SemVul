itemAddWebMedia()
{
    QDialog a;

    add_window.accept();
    Ui::AddWebMedia ui;
    ui.setupUi(&a);

    if (a.exec() == QDialog::Accepted &&
	!ui.nameLineEdit->text().isEmpty() &&
	!ui.deviceLineEdit->text().isEmpty()) {

	QTreeWidgetItem *item;
	item = itemAddToPlaylist(ui.nameLineEdit->text(),
		ui.deviceLineEdit->text());
	item->setText(3, "0");
    }
}
