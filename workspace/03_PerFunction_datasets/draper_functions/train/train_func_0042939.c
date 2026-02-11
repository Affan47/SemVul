normalize()
{
	float length = this->length();
	if(length == 0.0f or length == 1.0f)
		return;
	this->x /= length;
	this->y /= length;
	this->z /= length;
}
