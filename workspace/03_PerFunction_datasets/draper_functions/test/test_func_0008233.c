simplifyPattern (Tree value)
{
	Tree num;
	if (!getNumericProperty(value,num)) {
		if (!isBoxNumeric(value,num)) {
			num = value;
		}
		setNumericProperty(value,num);
	}
	return num;
}
