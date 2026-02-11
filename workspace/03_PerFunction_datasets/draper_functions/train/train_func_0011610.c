ms_container_finalize (MSContainer *container)
{
	int i;

	g_return_if_fail (container != NULL);

	if (container->free_blips && container->blips != NULL) {
		for (i = container->blips->len; i-- > 0 ; ) {
			MSEscherBlip *blip = g_ptr_array_index (container->blips, i);
			if (blip != NULL)
				ms_escher_blip_free (blip);
		}

		g_ptr_array_free (container->blips, TRUE);
		container->blips = NULL;
	}

	if (container->obj_queue != NULL) {
		GSList *ptr;
		for (ptr = container->obj_queue; ptr != NULL; ptr = ptr->next)
			ms_obj_delete (ptr->data);

		g_slist_free (container->obj_queue);
		container->obj_queue = NULL;
	}

	if (container->v7.externsheets != NULL) {
		g_ptr_array_free (container->v7.externsheets, TRUE);
		container->v7.externsheets = NULL;
	}
	if (container->v7.externnames != NULL) {
		for (i = container->v7.externnames->len; i-- > 0 ; )
			if (g_ptr_array_index (container->v7.externnames, i) != NULL) {
				GnmNamedExpr *nexpr = g_ptr_array_index (container->v7.externnames, i);
				if (nexpr != NULL) {


					if (expr_name_is_active (nexpr) &&
					    expr_name_is_placeholder (nexpr) &&

					    nexpr->ref_count == 2)
						expr_name_remove (nexpr);
					expr_name_unref (nexpr);
				}
			}
		g_ptr_array_free (container->v7.externnames, TRUE);
		container->v7.externnames = NULL;
	}
}
