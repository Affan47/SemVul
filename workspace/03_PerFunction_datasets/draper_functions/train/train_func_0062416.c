inv_rings(void)
{
    char buf[ROGUE_COLUMNS];

    if (r_rings == 0) {
	message(mesg[167], 0);
    } else {
	if (rogue.left_ring) {
	    get_desc(rogue.left_ring, buf, 1);
	    message(buf, 0);
	}
	if (rogue.right_ring) {
	    get_desc(rogue.right_ring, buf, 1);
	    message(buf, 0);
	}
    }
#if ORIGINAL
    if (wizard) {
	sprintf(buf,
		"ste %d, r_r %d, e_r %d, r_t %d, s_s %d, a_s %d, reg %d, r_e %d, s_i %d, m_a %d, aus %d",
		stealthy, r_rings, e_rings, r_teleport, sustain_strength,
		add_strength, regeneration, ring_exp, r_see_invisible,
		maintain_armor, auto_search);
	message(buf, 0);
    }
#endif
}
