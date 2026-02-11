text_transforms(xmlNodePtr node, double angle_deg,
		double x, double y)
{
	nudge_baseline(node);
	if (angle_deg <= 90 || angle_deg >= 270) {


		xmlChar *style_attr = (xmlChar*) "style";
		xmlChar *style = xmlGetProp(node, style_attr);
		if (NULL != style) {
			char * new_style = masprintf("%s;%s",
					(char *) style, "text-anchor:end");
			xmlSetProp(node, style_attr, (xmlChar *) new_style);
			free(style);
			free(new_style);
		}
		else {
			xmlSetProp(node, style_attr,
					(xmlChar*) "text-anchor:end");
		}
	} else {

		char * half_turn = masprintf("rotate(180,%g,%g)", x, y);
		prepend_transform(node, half_turn);
		free(half_turn);

		change_x_sign(node);
	}
}
