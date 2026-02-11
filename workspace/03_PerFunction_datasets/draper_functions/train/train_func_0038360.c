find_note ( char *p )
{
	int	note;
	int	done;
	int	octave;
	int	accidentals;
	char	*token;
	char	temp;

	static	int	note_vals[7] = { 69, 71, 60, 62, 64, 65, 67 };

	token = p;
	note = 0;
	done = FALSE;


	while ( *p != 0 && !done )
	{
		temp = tolower (*p);

		if (temp >= 'a' && temp <= 'g')
		{
			if (note == 0)
				note = note_vals[ temp - 'a' ];

			done = TRUE;
		}
		p++;
	}


	p = token;
	octave = 0;
	accidentals = 0;

	while ( *p != 0 )
	{
		if ( *p >= 'A' && *p <= 'G' )
		{
			octave = octave - 1;
		}
		else if ( *p >= 'a' && *p <= 'g' )
		{
			octave = octave + 1;
		}
		else if ( *p == '#' )
		{
			accidentals = accidentals + 1;
		}
		else if ( *p == '-' )
		{
			accidentals = accidentals - 1;
		}
		p++;
	}

	if (octave > 0)
		octave = octave - 1;

	note = note + 12 * octave + accidentals;


	if ( strchr (token, 'r') )
		note = REST;
	else if ( strchr (token, ']') || strchr (token, '_') )
		note = TIE;

	return (note);
}
