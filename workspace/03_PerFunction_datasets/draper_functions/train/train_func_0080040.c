resizeEvent(QResizeEvent *e)
{
	bool atEnd = verticalScrollBar()->value() ==
	             verticalScrollBar()->maximum();
	bool atStart = verticalScrollBar()->value() ==
	               verticalScrollBar()->minimum();
	double value = 0;
	if (!atEnd && !atStart)
		value = (double)verticalScrollBar()->maximum() /
		        (double)verticalScrollBar()->value();

	QTextEdit::resizeEvent(e);

	if (atEnd)
		verticalScrollBar()->setValue(verticalScrollBar()->maximum());
	else if (value != 0)
		verticalScrollBar()->setValue((int) ((double)verticalScrollBar()->maximum() / value));
}
