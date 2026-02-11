InsertLine(int lineDoc) {
	if (OneToOne()) {
		linesInDocument++;
	} else {
		visible->InsertSpace(lineDoc, 1);
		visible->SetValueAt(lineDoc, 1);
		expanded->InsertSpace(lineDoc, 1);
		expanded->SetValueAt(lineDoc, 1);
		heights->InsertSpace(lineDoc, 1);
		heights->SetValueAt(lineDoc, 1);
		int lineDisplay = DisplayFromDoc(lineDoc);
		displayLines->InsertPartition(lineDoc, lineDisplay);
		displayLines->InsertText(lineDoc, 1);
	}
}
