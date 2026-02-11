format_template_filter_style (GnmFormatTemplate *ft, GnmStyle *mstyle, gboolean fill_defaults)
{
	g_return_val_if_fail (ft != NULL, NULL);
	g_return_val_if_fail (mstyle != NULL, NULL);


	if (!fill_defaults) {
		if (!ft->number) {
			gnm_style_unset_element (mstyle, MSTYLE_FORMAT);
		}
		if (!ft->border) {
			gnm_style_unset_element (mstyle, MSTYLE_BORDER_TOP);
			gnm_style_unset_element (mstyle, MSTYLE_BORDER_BOTTOM);
			gnm_style_unset_element (mstyle, MSTYLE_BORDER_LEFT);
			gnm_style_unset_element (mstyle, MSTYLE_BORDER_RIGHT);
			gnm_style_unset_element (mstyle, MSTYLE_BORDER_DIAGONAL);
			gnm_style_unset_element (mstyle, MSTYLE_BORDER_REV_DIAGONAL);
		}
		if (!ft->font) {
			gnm_style_unset_element (mstyle, MSTYLE_FONT_NAME);
			gnm_style_unset_element (mstyle, MSTYLE_FONT_BOLD);
			gnm_style_unset_element (mstyle, MSTYLE_FONT_ITALIC);
			gnm_style_unset_element (mstyle, MSTYLE_FONT_UNDERLINE);
			gnm_style_unset_element (mstyle, MSTYLE_FONT_STRIKETHROUGH);
			gnm_style_unset_element (mstyle, MSTYLE_FONT_SIZE);

			gnm_style_unset_element (mstyle, MSTYLE_FONT_COLOR);
		}
		if (!ft->patterns) {
			gnm_style_unset_element (mstyle, MSTYLE_COLOR_BACK);
			gnm_style_unset_element (mstyle, MSTYLE_COLOR_PATTERN);
			gnm_style_unset_element (mstyle, MSTYLE_PATTERN);
		}
		if (!ft->alignment) {
			gnm_style_unset_element (mstyle, MSTYLE_ALIGN_V);
			gnm_style_unset_element (mstyle, MSTYLE_ALIGN_H);
		}
	} else {
		GnmStyle *gnm_style_default = gnm_style_new_default ();


		 if (!ft->number) {
			 gnm_style_merge_element (mstyle, gnm_style_default, MSTYLE_FORMAT);
		 }
		 if (!ft->border) {
			 gnm_style_merge_element (mstyle, gnm_style_default, MSTYLE_BORDER_TOP);
			 gnm_style_merge_element (mstyle, gnm_style_default, MSTYLE_BORDER_BOTTOM);
			 gnm_style_merge_element (mstyle, gnm_style_default, MSTYLE_BORDER_LEFT);
			 gnm_style_merge_element (mstyle, gnm_style_default, MSTYLE_BORDER_RIGHT);
			 gnm_style_merge_element (mstyle, gnm_style_default, MSTYLE_BORDER_DIAGONAL);
			 gnm_style_merge_element (mstyle, gnm_style_default, MSTYLE_BORDER_REV_DIAGONAL);
		 }
		 if (!ft->font) {
			 gnm_style_merge_element (mstyle, gnm_style_default, MSTYLE_FONT_NAME);
			 gnm_style_merge_element (mstyle, gnm_style_default, MSTYLE_FONT_BOLD);
			 gnm_style_merge_element (mstyle, gnm_style_default, MSTYLE_FONT_ITALIC);
			 gnm_style_merge_element (mstyle, gnm_style_default, MSTYLE_FONT_UNDERLINE);
			 gnm_style_merge_element (mstyle, gnm_style_default, MSTYLE_FONT_STRIKETHROUGH);
			 gnm_style_merge_element (mstyle, gnm_style_default, MSTYLE_FONT_SIZE);

			 gnm_style_merge_element (mstyle, gnm_style_default, MSTYLE_FONT_COLOR);
		 }
		 if (!ft->patterns) {
			 gnm_style_merge_element (mstyle, gnm_style_default, MSTYLE_COLOR_BACK);
			 gnm_style_merge_element (mstyle, gnm_style_default, MSTYLE_COLOR_PATTERN);
			 gnm_style_merge_element (mstyle, gnm_style_default, MSTYLE_PATTERN);
		 }
		 if (!ft->alignment) {
			 gnm_style_merge_element (mstyle, gnm_style_default, MSTYLE_ALIGN_V);
			 gnm_style_merge_element (mstyle, gnm_style_default, MSTYLE_ALIGN_H);
		 }

		 gnm_style_unref (gnm_style_default);
	}

	return mstyle;
}
