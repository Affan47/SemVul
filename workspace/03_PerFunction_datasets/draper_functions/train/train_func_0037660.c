newGame()
{
	delete m_scores;
	m_scores = new scores();
	m_scoresWidget -> setModel(m_scores);
	m_lateral -> nextTurn();

	m_scoresWidget -> header() -> setResizeMode(0, QHeaderView::Custom);
	m_scoresWidget -> resizeColumnToContents(0);
	statusBar()->hide();
	if (m_demoAction -> isChecked()) playComputer();
	connect(m_lateral, SIGNAL(rolled()), statusBar(), SLOT(hide()));
}
