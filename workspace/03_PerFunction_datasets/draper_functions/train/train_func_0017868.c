rehumanize()
{

	if (Unchanging && (u.mh < 1)) {
		killer_format = NO_KILLER_PREFIX;
		killer = "killed while stuck in creature form";
		done(DIED);
	}

	if (emits_light(youmonst.data))
	    del_light_source(LS_MONSTER, (genericptr_t)&youmonst);
	polyman("return to %s form!", urace.adj);

	if (u.uhp < 1) {
	    char kbuf[256];

	    Sprintf(kbuf, "reverting to unhealthy %s form", urace.adj);
	    killer_format = KILLED_BY;
	    killer = kbuf;
	    done(DIED);
	}
	if (!uarmg) selftouch("No longer petrify-resistant, you");
	nomul(0);

	flags.botl = 1;
	vision_full_recalc = 1;
	(void) encumber_msg();
}
