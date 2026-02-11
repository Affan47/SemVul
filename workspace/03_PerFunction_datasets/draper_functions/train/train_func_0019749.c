keyPressEvent(QKeyEvent *e)
{
	if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
		doOpenEvent();
	else
		Q3ListView::keyPressEvent(e);
}
