on_audioPlayButton_clicked(bool checked)
{
    if (checked) {

        emit audioPlayStarted(last_audio);

        ui->audioRecLabel->setText(QFileInfo(last_audio).fileName());
        ui->audioPlayButton->setToolTip(tr("Stop audio playback"));
        ui->audioRecButton->setEnabled(false);
    }
    else {
        ui->audioRecLabel->setText("<i>DSP</i>");
        ui->audioPlayButton->setToolTip(tr("Start playback of last recorded audio file"));
        emit audioPlayStopped();

        ui->audioRecButton->setEnabled(true);
    }
}
