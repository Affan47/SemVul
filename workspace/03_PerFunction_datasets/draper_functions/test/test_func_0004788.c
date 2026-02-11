actualSize() {
	QMessageBox::information(this, tr("Actual Size"),
				tr("It doesn't seem to be possible to automatically determine the actual physical size of the monitor, so "
				"'actual size' as currently implemented is only a guess. "
				"Your best bet would be to drag out a ruler part, then place a real (physical) ruler on top and zoom until they match up."
				));


	int dpi = this->physicalDpiX();
	int l = this->logicalDpiX();

	DebugDialog::debug(QString("actual size %1 %2").arg(dpi).arg(l));


	m_currentGraphicsView->absoluteZoom(dpi * 100.0 / GraphicsUtils::SVGDPI);
	m_zoomSlider->setValue(dpi * 100.0 / GraphicsUtils::SVGDPI);
}
