GK_do_framestep(int step, int render)
{
    if (Views) {
	if (step > 0 && step <= Viewsteps) {
	    gk_follow_frames(Views, Viewsteps, Keys, step, 1, render, Fmode);
	}
    }

    return;
}
