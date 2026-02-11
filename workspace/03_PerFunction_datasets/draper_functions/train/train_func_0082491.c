ReadLines(EReadTextFile flags, const wxMBConv& conv)
{
	wxArrayString lines;

	while (!Eof()) {
		bool result = true;

		wxString line = GetNextLine(flags, conv, &result);

		if (result) {
			lines.Add(line);
		}
	}

	return lines;
}
