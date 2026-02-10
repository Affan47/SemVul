accept()
{
	if( AttalSettings::getInstance()->getDispositionMode() != (AttalSettings::DispositionMode) _dispositionMode->currentItem() ) {
		AttalSettings::getInstance()->setDispositionMode( (AttalSettings::DispositionMode) _dispositionMode->currentItem() );
		emit sig_dispositions();
	}

	QDialog::accept ();
}
