nearest_neighbor_clustering(struct list *initial_clusters, double (*cmp)(struct cluster *, struct cluster *))
{
	struct cluster *top, *closest, *subtop;
	struct list   *stack;
	struct itable *active_clusters;
	double dclosest, dsubtop;

	int merge = 0;

	list_first_item(initial_clusters);
	top = list_next_item(initial_clusters);


	if(list_size(initial_clusters) < 2)
		return top;

	stack = list_create(0);
	list_push_head(stack, top);


	active_clusters = itable_create(0);
	while( (top = list_next_item(initial_clusters)) )
		itable_insert(active_clusters, (uintptr_t) top, (void *) top);

	do
	{


		top     = list_pop_head( stack );
		closest = cluster_nearest_neighbor(active_clusters, top, cmp);
		subtop  = list_peek_head( stack );

		dclosest = -1;
		dsubtop  = -1;

		if(closest)
			dclosest = cluster_ward_distance(top, closest);

		if(subtop)
			dsubtop = cluster_ward_distance(top, subtop);


		if( closest && subtop )
		{

			if(dclosest < dsubtop || ((dclosest == dsubtop) && (uintptr_t)closest < (uintptr_t)subtop))
				merge = 0;
			else
				merge = 1;
		}
		else if( subtop )
			merge = 1;
		else if( closest )
			merge = 0;
		else
			fatal("Zero clusters?\n");

		if(merge)
		{


			subtop = list_pop_head( stack );
			list_push_head(stack, cluster_merge(top, subtop));
		}
		else
		{


			itable_remove(active_clusters, (uintptr_t) closest);
			list_push_head(stack, top);
			list_push_head(stack, closest);
		}

		debug(D_DEBUG, "stack: %d  active: %d  closest: %lf subtop: %lf\n",
				list_size(stack), itable_size(active_clusters), dclosest, dsubtop);


		if(itable_size(active_clusters) == 0 && list_size(stack) > 3)
		{
			itable_delete(active_clusters);
			return nearest_neighbor_clustering(stack, cmp);
		}

	}while( !(itable_size(active_clusters) == 0 && list_size(stack) == 1) );


	top = list_pop_head(stack);

	list_delete(stack);
	itable_delete(active_clusters);

	return top;
}
