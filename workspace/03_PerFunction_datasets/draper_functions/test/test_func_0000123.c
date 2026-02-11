nodename() {
  TextGraphic* textgraphic = GetText();
  const char* text = textgraphic ? textgraphic->GetOriginal() : NULL;
  return text;
}
