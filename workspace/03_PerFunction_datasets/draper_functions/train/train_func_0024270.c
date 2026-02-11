update(RNG *rng)
    {
	if (!updateDouble(rng)) {
	    switch(state()) {
	    case SLICER_POSINF:
		throwNodeError(_gv->nodes().front(),
			       "Slicer stuck at value with infinite density");
		break;
	    case SLICER_NEGINF:
		throwNodeError(_gv->nodes().front(),
			       "Current value is inconsistent with data");
		break;
	    case SLICER_OK:
		break;
	    }
	}
    }
