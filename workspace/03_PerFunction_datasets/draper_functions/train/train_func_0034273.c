DrawDate () {
    if (showDate && date.len != 0) {
	const Font* f = output->GetFont();
	Coord dateYPos = ymax - f->Height();
	Coord dateXPos = 2;

	int availWidth = xmax - dateXPos - 2;
	int dayWidth = f->Width( date.text, 3 );
	int dayDateWidth = f->Width( date.text, 10 );
	int wholeWidth = f->Width( date.text, date.len );

	output->ClearRect(canvas, 0, ymax - f->Height(), xmax, ymax);
	if (wholeWidth < availWidth) {
	    output->Text(canvas, date.text, date.len, dateXPos, dateYPos);
	} else if (dayDateWidth < availWidth) {
	    output->Text(canvas, date.text, 10, dateXPos, dateYPos);
	} else if (dayWidth < availWidth) {
	    output->Text(canvas, date.text, 3, dateXPos, dateYPos);
	}
    }
}
