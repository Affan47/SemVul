changeOperation(int numW, int opW) {
	if(num!=numW) return;
	op=opW;
	QPixmap* pix=pixVide;

	if(op==Plus) {
		pix=pixPlus;
	} else
	if(op==Moins) {
		pix=pixMoins;
	} else
	if(op==Fois) {
		pix=pixFois;
	} else
	if(op==Divise) {
		pix=pixDivise;
	}

	if(cliquable){
		pbOperation->setIcon( *pix );
		pbOperation->setIconSize( QSize(28,28) );
	} else{
		lbOperation->setPixmap( *pix );
	}
}
