multi_char_to_unit(float val)
{
	float ret;

	ret = (float)val / 127.0f;
	if(ret > 1.0f){
		Int3();
		ret = 1.0f;
	}
	if(ret < -1.0f){
		Int3();
		ret = -1.0f;
	}

	return ret;
}
