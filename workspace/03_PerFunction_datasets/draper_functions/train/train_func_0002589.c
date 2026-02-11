first_caret_after(int pos) const
{
    const uint8_t *data = Type1Charstring::data();
    const uint8_t *edata = data + (pos < length() ? pos : length());

    while (data < edata) {
	if (*data >= 32 && *data <= 246)
	    data++;
	else if (*data < 32) {
	    if (*data == cEscape)
		data += 2;
	    else if (*data == cShortint)
		data += 3;
	    else
		data++;
	} else if (*data >= 247 && *data <= 254)
	    data += 2;
	else
	    data += 5;
    }

    const uint8_t *odata = Type1Charstring::data();
    return (data > odata + length() ? length() : data - odata);
}
