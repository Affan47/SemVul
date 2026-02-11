poplab(Void)
{
	register struct Labelblock  *lp;

	for(lp = labeltab ; lp < highlabtab ; ++lp)
		if(lp->labdefined)
		{

			if(lp->blklevel > blklevel)
				lp->labinacc = YES;
		}
		else if(lp->blklevel > blklevel)
		{

			lp->blklevel = blklevel;
		}
}
