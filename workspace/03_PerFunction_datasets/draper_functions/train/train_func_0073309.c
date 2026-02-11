fontIsItalic(FontObject fontObject) const
{
	GenFontKey(key,"/Italic");
	return mSettings->value(fullKey.c_str()).toBool();
}
