prepLoadImageAux(const QString & fileName, bool addName)
{
	InfoGraphicsView * infoGraphicsView = InfoGraphicsView::getInfoGraphicsView(this);
	if (infoGraphicsView != NULL) {
		infoGraphicsView->loadLogoImage(this, "", QSizeF(0,0), "", fileName, addName);
	}
}
