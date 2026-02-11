AddCharUTF(char *s, unsigned int len, bool treatAsDBCS) {
	bool isFillUp = ac.Active() && ac.IsFillUpChar(*s);
	if (!isFillUp) {
		Editor::AddCharUTF(s, len, treatAsDBCS);
	}
	if (ac.Active()) {
		AutoCompleteCharacterAdded(s[0]);


		if (isFillUp) {
			Editor::AddCharUTF(s, len, treatAsDBCS);
		}
	}
}
