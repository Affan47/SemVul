draw(const KEYOutput &output)
{
  const WPXPropertyList props(makePropList(m_style, output.getStyleContext()));
  output.getPainter()->openSpan(props);
  output.getPainter()->insertText(WPXString(m_text.c_str()));
  output.getPainter()->closeSpan();
}
