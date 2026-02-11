handle_histsize_command(String *args, int offset)
{
    History *hist;
    int maxsize = 0, size;
    const char *ptr;

    hist = globalhist;
    startopt(CS(args), "lgiw:");
    if (next_hist_opt(NULL, &offset, &hist, NULL))
        return shareval(val_zero);
    if (args->len - offset) {
        ptr = args->data + offset;
        if ((maxsize = numarg(&ptr)) <= 0) return shareval(val_zero);
	if (!resize_cqueue(&hist->cq, maxsize)) {
	    eprintf("not enough memory for %d lines.", maxsize);
	    maxsize = 0;
	}

    }
    size = hist->cq.maxsize ? hist->cq.maxsize : histsize;
    oprintf("%% %s history capacity %s %ld lines.",
        histname(hist), maxsize ? "changed to" : "is",
        size);
    hist->cq.index = hist->cq.last;
    return newint(size);
}
