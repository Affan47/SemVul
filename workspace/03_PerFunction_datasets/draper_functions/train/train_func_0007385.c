last_status(morewin)
    int		morewin;
{

    last_status_rec(topframe, (p_ls == 2
			  || (p_ls == 1 && (morewin || lastwin != firstwin))));
}
