rps_walk_fig (fig, layer, param)
rdsfig_list	*fig;
int		layer;
rps_par		*param;
{
	rdsrec_list	*r;


	for ( r = fig->LAYERTAB[layer] ;
	r != (rdsrec_list *) NULL ;
	r = r->NEXT) {
		rps_filter_rec (r);
	}


}
