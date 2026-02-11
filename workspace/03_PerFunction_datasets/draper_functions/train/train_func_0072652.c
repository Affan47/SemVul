save()
{
	if(_engine) {
		QString filen;
		filen = QFileDialog::getSaveFileName( 0 ,"", SAVE_PATH , "*.gam" );
		save( filen );
	}

}
