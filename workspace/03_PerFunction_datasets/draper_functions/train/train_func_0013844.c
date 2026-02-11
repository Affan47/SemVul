fb_aux(cp, map, prefix, buf, room)
register const data_obj	*cp;
struct keymap	*map;
char	*prefix,
	*buf;
size_t	room;
{
	char	*bufp = buf;

	if (map != NULL && !map->mark) {
		ZXchar	c1, c2;

		map->mark = YES;
		for (c1 = km_nextkey(map, 0); c1 < NCHARS; c1 = km_nextkey(map, c2 + 1)) {
			data_obj	*c1obj = km_getkey(map, c1);

			c2 = c1;
			if (c1obj == cp) {
				do ; while (++c2 < NCHARS && c1obj == km_getkey(map, c2));
				c2 -= 1;
				swritef(bufp, room - (bufp-buf),
					c1==c2? "%s%p, " : c1+1==c2? "%s{%p,%p}, " : "%s[%p-%p], ",
					prefix, c1, c2);
				bufp += strlen(bufp);
			}
			if (IsKeymap(c1obj)) {
				char	prefbuf[20];

#ifdef PCNONASCII

				if (c1 == PCNONASCII) {
					struct keymap	*pcm = (struct keymap *)c1obj;
					ZXchar	pc;

					c2 = c1;
					for (pc = km_nextkey(pcm, 0); pc < NCHARS; pc = km_nextkey(pcm, pc + 1)) {
						const char	*as = pc < elemsof(altseq)? altseq[pc] : NULL;
						data_obj	*pcobj = km_getkey(pcm, pc);

						if (pcobj == cp) {
							if (as == NULL)
								swritef(bufp, room - (bufp-buf),
									"%s%p %p, ", prefix, PCNONASCII, pc);
							else
								swritef(bufp, room - (bufp-buf),
									"%s%s, ", prefix, as);
							bufp += strlen(bufp);
						}
						if (IsKeymap(pcobj)) {
							if (as == NULL)
								swritef(prefbuf, sizeof(prefbuf),
									"%s%p %p ", prefix, PCNONASCII, pc);
							else
								swritef(prefbuf, sizeof(prefbuf),
									"%s%s ", prefix, as);
							bufp = fb_aux(cp, (struct keymap *) pcobj,
								prefbuf, bufp, room-(bufp-buf));
						}
					}
					continue;
				}
#endif
				swritef(prefbuf, sizeof(prefbuf), "%s%p ", prefix, c1);
				bufp = fb_aux(cp, (struct keymap *) c1obj, prefbuf, bufp,
					room-(bufp-buf));
			}
		}
		map->mark = NO;
	}
	return bufp;
}
