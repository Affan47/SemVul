fileBrowse()
{
    std::string s = QFileDialog::getOpenFileName(this,
                    "Browse For Tape Files",
                    Preferences::getInstance().configDir().c_str(),
                    tr("All files(*)")).toStdString();
    ui.filename->setText(s.c_str());

}
