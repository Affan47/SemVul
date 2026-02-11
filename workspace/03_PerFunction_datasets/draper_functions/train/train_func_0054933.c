markNewWordPosition()
{
	if (lyxrc.spellcheck_continuously && inTexted() && new_word_.empty()) {
		FontSpan nw = locateWord(WHOLE_WORD);
		if (nw.size() == 1) {
			LYXERR(Debug::DEBUG, "start new word: "
				<< " par: " << pit()
				<< " pos: " << nw.first);
			new_word_ = *this;
		}
	}
}
