ChangeCaseOfSelection(int caseMapping) {
	UndoGroup ug(pdoc);
	for (size_t r=0; r<sel.Count(); r++) {
		SelectionRange current = sel.Range(r);
		SelectionRange currentNoVS = current;
		currentNoVS.ClearVirtualSpace();
		size_t rangeBytes = currentNoVS.Length();
		if (rangeBytes > 0) {
			std::string sText = RangeText(currentNoVS.Start().Position(), currentNoVS.End().Position());

			std::string sMapped = CaseMapString(sText, caseMapping);

			if (sMapped != sText) {
				size_t firstDifference = 0;
				while (sMapped[firstDifference] == sText[firstDifference])
					firstDifference++;
				size_t lastDifferenceText = sText.size() - 1;
				size_t lastDifferenceMapped = sMapped.size() - 1;
				while (sMapped[lastDifferenceMapped] == sText[lastDifferenceText]) {
					lastDifferenceText--;
					lastDifferenceMapped--;
				}
				size_t endDifferenceText = sText.size() - 1 - lastDifferenceText;
				pdoc->DeleteChars(
					static_cast<int>(currentNoVS.Start().Position() + firstDifference),
					static_cast<int>(rangeBytes - firstDifference - endDifferenceText));
				pdoc->InsertString(
					static_cast<int>(currentNoVS.Start().Position() + firstDifference),
					sMapped.c_str() + firstDifference,
					static_cast<int>(lastDifferenceMapped - firstDifference + 1));

				int diffSizes = static_cast<int>(sMapped.size() - sText.size());
				if (diffSizes != 0) {
					if (current.anchor > current.caret)
						current.anchor.Add(diffSizes);
					else
						current.caret.Add(diffSizes);
				}
				sel.Range(r) = current;
			}
		}
	}
}
