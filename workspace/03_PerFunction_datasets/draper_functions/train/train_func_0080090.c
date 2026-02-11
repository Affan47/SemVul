askValue( const QString & value, bool & ok )
{
	return QInputDialog::getText( 0 ,"New item", "Enter new item text: ", QLineEdit::Normal, value, &ok );
}
