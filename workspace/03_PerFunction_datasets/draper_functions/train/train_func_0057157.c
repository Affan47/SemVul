applyView()
{
	docstring dbs;

	unsigned int maxCount = databaseLW->count();
	for (unsigned int i = 0; i < maxCount; i++) {
		if (i != 0)
			dbs += ',';
		QString item = databaseLW->item(i)->text();
		docstring bibfile = qstring_to_ucs4(item);
		dbs += bibfile;
	}

	params_["bibfiles"] = dbs;

	docstring const bibstyle = qstring_to_ucs4(styleCB->currentText());
	bool const bibtotoc = bibtocCB->isChecked();

	if (bibtotoc && !bibstyle.empty()) {

		params_["options"] = "bibtotoc," + bibstyle;
	} else if (bibtotoc) {

		params_["options"] = from_ascii("bibtotoc");
	} else {


		params_["options"] = bibstyle;
	}

	int btp = btPrintCO->currentIndex();

	if (usingBibtopic()) {


		switch (btp) {
		case 0:
			params_["btprint"] = from_ascii("btPrintCited");
			break;
		case 1:
			params_["btprint"] = from_ascii("btPrintNotCited");
			break;
		case 2:
			params_["btprint"] = from_ascii("btPrintAll");
			break;
		}
	} else {
		switch (btp) {
		case 0:
			params_["btprint"] = docstring();
			break;
		case 1:

			params_["btprint"] = from_ascii("btPrintAll");
			break;
		}
	}
}
