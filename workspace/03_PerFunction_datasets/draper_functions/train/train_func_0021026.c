cb_html_attrs_as_string (GsfOutput *output, PangoAttribute *a, html_version_t version)
{

	char const *closure = NULL;

	switch (a->klass->type) {
	case PANGO_ATTR_FAMILY :
		break;
	case PANGO_ATTR_SIZE :
		break;
	case PANGO_ATTR_RISE:
		if (((PangoAttrInt *)a)->value > 5) {
			gsf_output_puts (output, "<sup>");
			closure = "</sup>";
		} else if (((PangoAttrInt *)a)->value < -5) {
			gsf_output_puts (output, "<sub>");
			closure = "</sub>";
		}
		break;
	case PANGO_ATTR_STYLE :
		if (((PangoAttrInt *)a)->value == PANGO_STYLE_ITALIC) {
			gsf_output_puts (output, "<i>");
			closure = "</i>";
		}
		break;
	case PANGO_ATTR_WEIGHT :
		if (((PangoAttrInt *)a)->value > 600){
			gsf_output_puts (output, "<b>");
			closure = "</b>";
		}
		break;
	case PANGO_ATTR_STRIKETHROUGH :
		if (((PangoAttrInt *)a)->value == 1) {
			if (version == HTML32) {
				gsf_output_puts (output, "<strike>");
				closure = "</strike>";
			} else {
				gsf_output_puts
					(output,
					 "<span style=\"text-decoration: "
					 "line-through;\">");
				closure = "</span>";
			}
		}
		break;
	case PANGO_ATTR_UNDERLINE :
		if ((version != HTML40) &&
		    (((PangoAttrInt *)a)->value != PANGO_UNDERLINE_NONE)) {
			gsf_output_puts (output, "<u>");
			closure = "</u>";
		}
		break;
	case PANGO_ATTR_FOREGROUND :


		break;
	default :
		if (a->klass->type ==
		    go_pango_attr_subscript_get_attr_type ()) {
			if (((GOPangoAttrSubscript *)a)->val) {
				gsf_output_puts (output, "<sub>");
				closure = "</sub>";
			}
		} else if (a->klass->type ==
			   go_pango_attr_superscript_get_attr_type ()) {
			if (((GOPangoAttrSuperscript *)a)->val) {
				gsf_output_puts (output, "<sup>");
				closure = "</sup>";
			}
		}
		break;
	}

	return closure;
}
