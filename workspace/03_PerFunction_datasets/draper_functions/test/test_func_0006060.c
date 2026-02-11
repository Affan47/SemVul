gen_full_envelope(int Size, int Attack, int Release)
{
	float p_fade = 0.0f;
	float* p_envelope = new float[Size];

	p_envelope[0] = 0.0f;
	p_envelope[1] = 0.0f;

	float p_fadeStep = 1.0f / (Attack - 2);
	p_fade = 0.0f;
	for (int i = 2 ; i < Attack ; i++)
	{
		if(p_fade < 1)
		{
			p_envelope[i] = p_fade;
		}
		else
		{
			p_envelope[i] = 1.0f;
		}
		p_fade += p_fadeStep;
	}

	for (int i = Attack ; i < Size - Release ; i++)
	{
		p_envelope[i] = 1.0f;
	}

	p_fadeStep = 1.0f / (Release - 2);
	p_fade = 1.0f;
	for (int i = Size - Release ; i < Size - 2; i++)
	{
		p_fade -= p_fadeStep;
		if(p_fade > 0)
		{
			p_envelope[i] = p_fade;
		}
		else
		{
			p_envelope[i] = 0.0f;
		}
	}

	p_envelope[Size - 2] = 0.0f;
	p_envelope[Size - 1] = 0.0f;

	return p_envelope;
}
