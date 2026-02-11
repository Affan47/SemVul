on_gainSlider_valueChanged(int gain)
{
    ui->gainLabel->setText(QString("%1 dB").arg(ui->gainSlider->value()));
    emit gainChanged(gain);
}
