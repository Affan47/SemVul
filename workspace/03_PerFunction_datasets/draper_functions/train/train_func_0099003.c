accept()
{
	m_theme.setName(m_name->text());

	m_theme.setBackgroundType(m_background_type->currentIndex());
	m_theme.setBackgroundColor(m_background_color->color());
	m_theme.setBackgroundImage(m_background_image->toString());

	m_theme.setForegroundColor(m_foreground_color->color());
	m_theme.setForegroundOpacity(m_foreground_opacity->value());
	m_theme.setForegroundWidth(m_foreground_width->value());
	m_theme.setForegroundRounding(m_foreground_rounding->value());
	m_theme.setForegroundMargin(m_foreground_margin->value());
	m_theme.setForegroundPadding(m_foreground_padding->value());
	m_theme.setForegroundPosition(m_foreground_position->currentIndex());

	m_theme.setTextColor(m_text_color->color());
	QFont font = m_font_names->currentFont();
	font.setPointSizeF(m_font_sizes->currentText().toDouble());
	m_theme.setTextFont(font);
	m_theme.setMisspelledColor(m_misspelled_color->color());

	m_theme.setIndentFirstLine(m_indent_first_line->isChecked());
	m_theme.setLineSpacing(m_line_spacing->value());
	m_theme.setSpacingAboveParagraph(m_spacing_above_paragraph->value());
	m_theme.setSpacingBelowParagraph(m_spacing_below_paragraph->value());

	savePreview();

	QDialog::accept();
}
