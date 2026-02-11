apply( QTextTableFormat *format ) const
{
  if ( ! isValid ) {
    return;
  }
  QVector<QTextLength> lengths = format->columnWidthConstraints();
  lengths.append( QTextLength( QTextLength::FixedLength, mWidth ) );

  format->setColumnWidthConstraints( lengths );
}
