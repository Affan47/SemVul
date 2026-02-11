wrong_password_slot()
{
    QMessageBox::information(this, tr("Wrong password"), tr("Login failed : Wrong password"));
    emit remove_tab_signal(client_nbr);
}
