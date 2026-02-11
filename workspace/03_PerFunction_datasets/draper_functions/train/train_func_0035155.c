aboutApplication()
{
    AboutDialog *aboutDialog = new AboutDialog(this);
    aboutDialog->setAttribute(Qt::WA_DeleteOnClose);
    aboutDialog->show();
}
