makeBreadboardSipSvg(const QString & expectedFileName)
{
	QStringList pieces = expectedFileName.split("_");
	if (pieces.count() != 5) return "";

	int pins = pieces.at(2).toInt();
	int increment = 10;
	double totalWidth = (pins * increment);

	QString svg = TextUtils::incrementTemplate(":/resources/templates/generic_sip_bread_template.txt", 1, increment * (pins - 2), TextUtils::incMultiplyPinFunction, TextUtils::noCopyPinFunction, NULL);

	QString repeat("<rect id='connector%1pin' x='[13.5]' y='25.66' fill='#8C8C8C' width='3' height='4.34'/>\n"
					"<rect id='connector%1terminal' x='[13.5]' y='27.0' fill='#8C8C8C' width='3' height='3'/>\n"
					"<polygon fill='#8C8C8C' points='[11.5],25.66 [11.5],26.74 [13.5],27.66 [16.5],27.66 [18.5],26.74 [18.5],25.66'/>\n");

	QString repeats;
	if (pins > 2) {
		repeats = TextUtils::incrementTemplateString(repeat, pins - 2, increment, TextUtils::standardMultiplyPinFunction, TextUtils::incCopyPinFunction, NULL);
	}

	return svg.arg(totalWidth / 100).arg(pins - 1).arg(repeats);

}
