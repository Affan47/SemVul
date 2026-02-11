keyPressEvent(QKeyEvent *e)
{
	if(e->key() == Qt::Key_Escape)
		close();
	else {
		e->ignore();
	}
}
