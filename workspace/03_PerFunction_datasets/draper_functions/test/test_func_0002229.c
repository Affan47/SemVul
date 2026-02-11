makeRotationFrame() {
	m_rotationLabel = new QLabel(tr("rotation"), this);
	m_rotationLabel->setObjectName("propNameLabel");
	m_rotationLabel->setWordWrap(true);

    m_rotationFrame = new QFrame(this);
    QHBoxLayout * rotationLayout = new QHBoxLayout();
	rotationLayout->setSpacing(0);
	rotationLayout->setContentsMargins(0, 0, 0, 0);
    m_rotationFrame->setObjectName("propValueFrame");

	m_rotEdit = new QDoubleSpinBox;
    m_rotEdit->setDecimals(1);
    m_rotEdit->setRange(-360, 360);
    m_rotEdit->setKeyboardTracking(false);
    m_rotEdit->setObjectName("infoViewDoubleSpinBox");
    m_rotEdit->setMaximumWidth(MaxSpinBoxWidth);
    m_rotEdit->setMinimumWidth(MaxSpinBoxWidth);
    rotationLayout->addWidget(m_rotEdit);

    rotationLayout->addSpacing(AfterSpinBoxWidth);

	QLabel * label = new QLabel(tr("degrees"), this);
    label->setObjectName("infoViewSpinBoxLabel");
    rotationLayout->addWidget(label);

    rotationLayout->addSpacerItem(new QSpacerItem(1,1, QSizePolicy::Expanding));

    m_rotationFrame->setLayout(rotationLayout);

    connect(m_rotEdit, SIGNAL(valueChanged(double)), this, SLOT(rotEntry()));
}
