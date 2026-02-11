reset_output(audio_output_t *ao)
{
	if(!param.usebuffer)
	{
		close_output(ao);
		return open_output(ao);
	}
	else return 0;
}
