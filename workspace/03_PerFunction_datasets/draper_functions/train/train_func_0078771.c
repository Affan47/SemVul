updateLabel(int idx, double value)
{
    QLabel *label = value_labels.at(idx);

    label->setText(QString("%1 dB").arg(value, 0, 'f', 1));
}
