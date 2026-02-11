mousePressEvent(QMouseEvent *event) {
	if(reglable){
		if(event->button()==Qt::RightButton) {
			clicPlus=false;
		} else {
			clicPlus=true;
		}
		pbClicked();
		timer->start(150);
	} else
	if(cliquable){
		cliquable=false;
		colorise(2);
		emit valeur(num,lcd->intValue());
	}
}
