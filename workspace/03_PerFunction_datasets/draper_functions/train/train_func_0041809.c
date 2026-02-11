layoutDuplicate()
{

    _multiView->saveLayout(QString("Layout%1-MainView").arg(_layoutCurrent),
			   traceKey());
    _layoutCurrent = _layoutCount;
    _layoutCount++;

    updateLayoutActions();

    qDebug() << "QCGTopLevel::layoutDuplicate: count " << _layoutCount;
}
