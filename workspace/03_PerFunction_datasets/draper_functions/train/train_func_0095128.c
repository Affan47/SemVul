flush()
{
    Type1Writer::flush();
    if (_save.length()) {
	fputc(128, _f);
	fputc(_binary ? 2 : 1, _f);
	long l = _save.length();
	fputc(l & 0xFF, _f);
	fputc((l >> 8) & 0xFF, _f);
	fputc((l >> 16) & 0xFF, _f);
	fputc((l >> 24) & 0xFF, _f);
	ssize_t result = fwrite(_save.data(), 1, _save.length(), _f);
	(void) result;
	_save.clear();
    }
}
