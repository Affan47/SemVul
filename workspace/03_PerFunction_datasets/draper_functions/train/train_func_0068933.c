IF_CharEvent( inputField_t *field, int key )
{
	int len;

	if (key < 32 || key > 127)
		return;

	if (field->cursorPos >= MAX_FIELD_TEXT-1)
		return;

	len = strlen(field->text[field->editLine]);
	if (!Key_GetOverstrikeMode()) {
		if(len >= MAX_FIELD_TEXT-1)
			return;
		memmove( field->text[field->editLine] + field->cursorPos + 1, field->text[field->editLine] + field->cursorPos, len - field->cursorPos + 1 );
	}


	field->text[field->editLine][field->cursorPos] = key;
	field->cursorPos++;

	if (field->cursorPos == len + 1)
		field->text[field->editLine][field->cursorPos] = 0;
}
