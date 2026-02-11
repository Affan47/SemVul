init()
{
	m_expanded = true;
	m_always_expanded = false;
	m_under_mouse = false;

	setAttribute(Qt::WA_TranslucentBackground);
	setStyleSheet("QLabel { color: white } Alert { color: white; background-color: black }");

	if (parent()) {
		parent()->installEventFilter(this);
	}

	m_expander = new QToolButton(this);
	m_expander->setAutoRaise(true);
	m_expander->setIconSize(QSize(16,16));
	m_expander->hide();
	connect(m_expander, SIGNAL(clicked()), this, SLOT(expanderToggled()));

	m_pixmap = new QLabel(this);
	m_pixmap->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

	m_text = new QLabel(this);
	m_text->setTextInteractionFlags(Qt::TextSelectableByMouse);
	m_text->setWordWrap(true);

	QToolButton* close = new QToolButton(this);
	close->setAutoRaise(true);
	close->setIconSize(QSize(16,16));
	close->setIcon(QIcon::fromTheme("window-close"));
	close->setToolTip(tr("Close (%1)").arg(ActionManager::instance()->action("DismissAlert")->shortcut().toString(QKeySequence::NativeText)));
	connect(close, SIGNAL(clicked()), this, SLOT(fadeOut()));

	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setMargin(7);
	layout->setSpacing(6);
	layout->addWidget(m_expander, 0, Qt::AlignHCenter | Qt::AlignBottom);
	layout->addWidget(m_pixmap);
	layout->addWidget(m_text, 1);
	layout->addWidget(close, 0, Qt::AlignHCenter | Qt::AlignTop);

	QGraphicsOpacityEffect* fade_effect = new QGraphicsOpacityEffect(this);
	fade_effect->setOpacity(0.0);
	setGraphicsEffect(fade_effect);

	m_fade_timer = new QTimeLine(240, this);
	connect(m_fade_timer, SIGNAL(valueChanged(qreal)), fade_effect, SLOT(setOpacity(qreal)));
}
