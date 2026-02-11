do_hist_pgno(struct vtwin *w)
{
    if (hist(w, -1)->pgno)
    {
	w->hist_top--;
	query_page(w, hist(w, 0)->pgno, hist(w, 0)->subno);
    }
    else
	err(w, "Empty history.");
}
