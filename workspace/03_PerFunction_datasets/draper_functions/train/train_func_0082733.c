makeSchematicSvg(const QString & expectedFileName)
{
	QStringList pieces = expectedFileName.split("_");
	if (pieces.count() < 7) return "";

    QString spacingString;
    int pins = TextUtils::getPinsAndSpacing(expectedFileName, spacingString);
	QString form = expectedFileName.contains("female") ? "female" :"male";
    bool sizeTenth = expectedFileName.contains("10thin");
    bool isDouble = sizeTenth && expectedFileName.contains("double");

    double width, unitHeight;
    double divisor = isDouble ? 2 : 1;
    if (sizeTenth) {
        width = isDouble ? 0.5 : 0.2;
        unitHeight = GraphicsUtils::StandardSchematicSeparation10thinMils / 1000;
    }
    else {
        unitHeight = GraphicsUtils::StandardSchematicSeparationMils / 1000;
        width = 0.87;
    }
	double unitHeightPoints = unitHeight * 72;

	QString header("<?xml version='1.0' encoding='utf-8'?>\n"
				"<svg version='1.2' baseProfile='tiny' id='svg2' xmlns:svg='http://www.w3.org/2000/svg' "
				"xmlns='http://www.w3.org/2000/svg'  x='0in' y='0in' width='%3in' "
				"height='%1in' viewBox='0 0 %4 %2'>\n"
				"<g id='schematic' >\n");


	QString svg = header.arg(unitHeight * pins / divisor).arg(unitHeightPoints * pins / divisor).arg(width).arg(width * 72);

    QString templateFile = QString(":/resources/templates/generic_%1_%2%3pin_header_schem_template.txt")
                                                .arg(form.contains("female") ? "female" : "male")
                                                .arg(sizeTenth ? "10thin_" : "")
                                                .arg(isDouble ? "double_" : "")
                                                ;
    if (sizeTenth) {
        if (isDouble) {
	        svg += TextUtils::incrementTemplate(templateFile, pins / 2, unitHeightPoints, TextUtils::standardMultiplyPinFunction, doubleCopyPinFunction, NULL);
        }
        else {
	        svg += TextUtils::incrementTemplate(templateFile, pins, unitHeightPoints, TextUtils::standardMultiplyPinFunction, stdIncCopyPinFunction, NULL);
        }
    }
    else {
	    svg += TextUtils::incrementTemplate(templateFile, pins, unitHeightPoints, TextUtils::standardMultiplyPinFunction, TextUtils::standardCopyPinFunction, NULL);
    }


	svg += "</g>\n</svg>";

	return svg;
}
