GK_update_frames(void)
{
    Keylist *k;
    int loop = 0;

    if (Keys) {
	if (Numkeys > 1) {
	    k = Keytail;
	    Keyendpos = k->pos;

	    if (k->fields[KF_FROMX] == Keys->fields[KF_FROMX] &&
		k->fields[KF_FROMY] == Keys->fields[KF_FROMY] &&
		k->fields[KF_FROMZ] == Keys->fields[KF_FROMZ]) {
		loop = 1;
	    }
	}

	Keystartpos = Keys->pos;
    }

    if (Interpmode == KF_LINEAR && Numkeys > 1) {
	if (Views) {
	    free(Views);
	    Views = NULL;
	}

	Views = gk_make_linear_framesfromkeys(Keys, Numkeys, Viewsteps, loop);

	if (!Views) {
	    G_warning(_("Check no. of frames requested and keyframes marked"));
	}
    }
    else if (Numkeys > 2) {
	if (Views) {
	    free(Views);
	    Views = NULL;
	}

	Views = gk_make_framesfromkeys
	    (Keys, Numkeys, Viewsteps, loop, 1.0 - Tension);

	if (!Views) {
	    G_warning(_("Check no. of frames requested and keyframes marked"));
	}
    }

    return;
}
