stopAudioRecorder(void)
{
    if (ui->audioRecButton->isChecked())
        ui->audioRecButton->click();
    else
        qDebug() << __func__ << "No audio recording in progress";
}
