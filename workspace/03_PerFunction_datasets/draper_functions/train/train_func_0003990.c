makeBreadboardShroudedSvg(int pins)
{
	QString header("<?xml version='1.0' encoding='utf-8'?>\n"
					"<svg version='1.2' baseProfile='tiny' "
					"xmlns='http://www.w3.org/2000/svg'  x='0in' y='0in' width='%1in' "
					"height='0.3484167in' viewBox='0 0 [400] 348.4167in'>\n"
					"<g id='breadboard' >\n"
					"<rect id='bgnd' x='0' y='0' width='[400]' height='348.4167' stroke='none' stroke-width='0' fill='#1a1a1a' />\n"
					"<rect id='top inset' x='0' y='0' width='[400]' height='38.861' stroke='none' stroke-width='0' fill='#2a2a29' />\n"
					"<rect id='bottom inset' x='0' y='309.5557' width='[400]' height='38.861' stroke='none' stroke-width='0' fill='#595959' />\n"
					"<path id='left inset'  d='M0,0 0,348.4167 38.861,309.5557 38.861,38.861z' stroke='none' stroke-width='0' fill='#373737' />\n"
					"<path id='right inset'  d='M[400],0 [400],348.4167 [361.139],309.5557 [361.139],38.861z' stroke='none' stroke-width='0' fill='#474747' />\n"
					"<rect id='top border' x='0' y='0' width='[400]' height='24.972' stroke='none' stroke-width='0' fill='#404040' />\n"
					"<rect id='bottom border' x='0' y='323.4447' width='[400]' height='24.972' stroke='none' stroke-width='0' fill='#404040' />\n"
					"<rect id='left border' x='0' y='0' width='24.972' height='348.4167' stroke='none' stroke-width='0' fill='#404040' />\n"
					"<rect id='right border' x='[375.028]' y='0' width='24.972' height='348.4167' stroke='none' stroke-width='0' fill='#404040' />\n"
					"%2\n"
					"%3\n"
					"<rect id='slot' x='{115.9514}' y='280.4973' width='168.0972' height='67.9194' stroke='none' stroke-width='0' fill='#1a1a1a' />\n"
					"</g>\n"
					"</svg>\n"
				);

	QString repeatT("<rect id='upper connector bgnd' x='[173.618055]' y='95.972535' width='52.76389' height='52.76389' stroke='none' stroke-width='0' fill='#141414' />\n"
					"<rect id='connector%1pin' x='[184.03472]' y='106.3892' width='31.93056' height='31.93056' stroke='none' stroke-width='0' fill='#8c8663' />\n"
					"<rect id='upper connector top inset' x='[184.03472]' y='106.3892' width='31.93056' height='7.75' stroke='none' stroke-width='0' fill='#B8AF82' />\n"
					"<rect id='upper connector bottom inset' x='[184.03472]' y='130.56976' width='31.93056' height='7.75' stroke='none' stroke-width='0' fill='#5E5B43' />\n"
					"<path id='upper connector left inset' d='M[184.03472],106.3892 [184.03472],138.31976 [191.7847],130.56976 [191.7847],114.1392z' stroke='none' stroke-width='0' fill='#9A916C' />\n"
					"<path id='upper connector right inset' d='M[215.96522],106.3892 [215.96522],138.31976 [208.21522],130.56976 [208.21522],114.1392z' stroke='none' stroke-width='0' fill='#9A916C' />\n"
				);

	QString repeatB("<rect id='lower connector bgnd' x='[173.618055]' y='195.972535' width='52.76389' height='52.76389' stroke='none' stroke-width='0' fill='#141414' />\n"
					"<rect id='connector%1pin' x='[184.03472]' y='206.3892' width='31.93056' height='31.93056' stroke='none' stroke-width='0' fill='#8c8663' />\n"
					"<rect id='lower connector top inset' x='[184.03472]' y='206.3892' width='31.93056' height='7.75' stroke='none' stroke-width='0' fill='#B8AF82' />\n"
					"<rect id='lower connector bottom inset' x='[184.03472]' y='230.56976' width='31.93056' height='7.75' stroke='none' stroke-width='0' fill='#5E5B43' />\n"
					"<path id='lower connector left inset' d='M[184.03472],206.3892 [184.03472],238.31976 [191.7847],230.56976 [191.7847],214.1392z' stroke='none' stroke-width='0' fill='#9A916C' />\n"
					"<path id='lower connector right inset' d='M[215.96522],206.3892 [215.96522],238.31976 [208.21522],230.56976 [208.21522],214.1392z' stroke='none' stroke-width='0' fill='#9A916C' />\n"
				);


	double increment = 100;

	QString svg = TextUtils::incrementTemplateString(header, 1, increment * (pins - 2) / 2, TextUtils::incMultiplyPinFunction, TextUtils::noCopyPinFunction, NULL);
	svg.replace("{", "[");
	svg.replace("}", "]");
	svg = TextUtils::incrementTemplateString(svg, 1, increment * (pins - 2) / 4, TextUtils::incMultiplyPinFunction, TextUtils::noCopyPinFunction, NULL);

	int userData[2];
	userData[0] = pins;
	userData[1] = 1;
	QString repeatTs = TextUtils::incrementTemplateString(repeatT, pins / 2, increment, TextUtils::standardMultiplyPinFunction, TextUtils::negIncCopyPinFunction, userData);
	QString repeatBs = TextUtils::incrementTemplateString(repeatB, pins / 2, increment, TextUtils::standardMultiplyPinFunction, TextUtils::standardCopyPinFunction, NULL);

	return svg.arg(TextUtils::getViewBoxCoord(svg, 2) / 1000.0).arg(repeatTs).arg(repeatBs);
}
