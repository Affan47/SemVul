setBinWidthFromLineEdit()
{
    if (bactive) return;
    setBin(binWidthLineEdit->text().toDouble());
}
