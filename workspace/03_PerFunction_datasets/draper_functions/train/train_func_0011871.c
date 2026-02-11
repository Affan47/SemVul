EnsureStyledTo(int pos) {
	if ((enteredStyling == 0) && (pos > GetEndStyled())) {
		IncrementStyleClock();
		if (pli && !pli->UseContainerLexing()) {
			int lineEndStyled = LineFromPosition(GetEndStyled());
			int endStyledTo = LineStart(lineEndStyled);
			pli->Colourise(endStyledTo, pos);
		} else {

			for (int i = 0; pos > GetEndStyled() && i < lenWatchers; i++) {
				watchers[i].watcher->NotifyStyleNeeded(this, watchers[i].userData, pos);
			}
		}
	}
}
