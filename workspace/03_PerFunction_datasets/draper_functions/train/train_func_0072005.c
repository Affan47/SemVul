FinishBuffering(boolean refresh_needed)
{
    if (refresh_needed)
	canvas->rep()->swapbuffers();
    canvas->rep()->xdrawable_ = canvas->rep()->copybuffer_;
}
