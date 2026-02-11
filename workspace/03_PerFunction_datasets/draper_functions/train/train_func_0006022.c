updateSourceDirectory(const QString& dir)
{
  if(this->SourceDirectory->text() != dir)
    {
    this->SourceDirectory->blockSignals(true);
    this->SourceDirectory->setText(dir);
    this->SourceDirectory->blockSignals(false);
    }
}
