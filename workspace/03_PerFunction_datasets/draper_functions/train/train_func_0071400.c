embed(QWidget * widget)
{
	if (_embededProxy) delete _embededProxy;
	else if (_embeded) delete _embeded;
	_embeded = widget;
	_embededProxy = 0;
	if (!_embeded) return;

	if (true or _embeded->testAttribute(Qt::WA_PaintOnScreen))
	{


		_embeded->setParent(_canvas);
		_embeded->show();
	}
	else
	{

		_embeded->setParent(0);
		_embededProxy = new QGraphicsProxyWidget(this);
		_embededProxy->setWidget(_embeded);
	}
}
