cut_tune(float lwidth, float indent)
{
	struct SYMBOL *s, *s2;
	int i, bar_time, wmeasure;
	float xmin;


	for (s = tsfirst; ; s = s->ts_next) {
		if (s->shrink == 0)
			continue;
		if (s->type != CLEF && s->type != KEYSIG)
			break;
		lwidth -= s->shrink;
	}
	if (cfmt.continueall) {
		set_lines(s, 0, lwidth, indent);
		return;
	}


	if ((i = cfmt.barsperstaff) != 0) {
		wmeasure = voice_tb[cursys->top_voice].meter.wmeasure;
		bar_time = s->time + wmeasure;
		s2 = s;
		for ( ; s != 0; s = s->ts_next) {
			switch (s->type) {
			case TIMESIG:
				wmeasure = s->as.u.meter.wmeasure;
				bar_time = s->time + wmeasure;
			default:
				continue;
			case BAR:
				break;
			}
			if (s->time < bar_time)
				continue;
			bar_time = s->time + wmeasure;
			if (--i > 0)
				continue;
			s->sflags |= S_EOLN;
			i = cfmt.barsperstaff;
		}
		s = s2;
	}


	xmin = indent;
	s2 = s;
	for ( ; s != 0; s = s->ts_next) {
		if (!(s->sflags & S_SEQST))
			continue;
		xmin += s->shrink;
		if (xmin > lwidth) {
			if (cfmt.linewarn)
				error(0, s, "Line overfull (%.0fpt of %.0fpt)",
					xmin, lwidth);
			for (s = s->ts_next; s != 0; s = s->ts_next) {
				if (s->sflags & S_EOLN)
					break;
			}
			s = s2 = set_lines(s2, s, lwidth, indent);
			if (s == 0)
				break;
			xmin = s->shrink;
			indent = 0;
		}
		if (!(s->sflags & S_EOLN))
			continue;
		s2 = set_nl(s);
		s->sflags &= ~S_EOLN;
		s = s2;
		if (s == 0)
			break;
		xmin = s->shrink;
		indent = 0;
	}
}
