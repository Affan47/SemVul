closeFile(bool force)
{
  int retval = QMessageBox::No;
  if( _delta.numEdits() ) {
    QString message =
      "Save changes to \"" + QString(_reader.filename()) + "\"?";
    if( force ) {
      retval = QMessageBox::warning( this,
				     PROGRAM_STRING,
				     message,
				     QMessageBox::Yes,
				     QMessageBox::No );
    } else {
      retval = QMessageBox::warning( this,
				     PROGRAM_STRING,
				     message,
				     QMessageBox::Yes,
				     QMessageBox::No,
				     QMessageBox::Cancel);
    }
  }
  if( retval == QMessageBox::Yes )
    save();
  return retval;
}
