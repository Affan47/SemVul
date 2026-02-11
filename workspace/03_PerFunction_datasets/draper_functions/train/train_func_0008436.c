setInitialSize() {
	double w =  m_modelPart->localProp("width").toDouble();
	if (w == 0) {

		QSizeF sz = this->boundingRect().size();
		modelPart()->setLocalProp("width", GraphicsUtils::pixels2mm(sz.width(), GraphicsUtils::SVGDPI));
		modelPart()->setLocalProp("height", GraphicsUtils::pixels2mm(sz.height(), GraphicsUtils::SVGDPI));
	}
}
