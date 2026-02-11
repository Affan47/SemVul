slot_new_game()
{
	if(keep_game())
		return;

	if(m_newgame->exec()==QDialog::Accepted) {
		m_view->newGame(m_newgame->rules(), m_newgame->freePlacement(),
				m_newgame->name(),
				m_newgame->isWhite(), m_newgame->opponent(),
				m_newgame->opponentName(), m_newgame->skill());
	}
}
