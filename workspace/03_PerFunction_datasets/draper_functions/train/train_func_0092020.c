hud_reticle_list_update(object *objp, float measure, int dot_flag)
{
	reticle_list	*rl, *new_rl;
	int				i;
	SCP_list<CJumpNode>::iterator jnp;

	if (objp->type == OBJ_JUMP_NODE) {
		for (jnp = Jump_nodes.begin(); jnp != Jump_nodes.end(); ++jnp) {
			if( jnp->GetSCPObject() != objp )
				continue;

			if( jnp->IsHidden() )
				return;
		}
	}

	for ( rl = GET_FIRST(&Reticle_cur_list); rl != END_OF_LIST(&Reticle_cur_list); rl = GET_NEXT(rl) ) {
		if ( rl->objp == objp )
			return;
	}

	i = hud_reticle_list_find_free();
	if ( i == -1 )
		return;

	new_rl = &Reticle_list[i];
	new_rl->flags |= RL_USED;
	hud_stuff_reticle_list(new_rl, objp, measure, dot_flag);

	int was_inserted = 0;

	if ( EMPTY(&Reticle_cur_list) ) {
		list_insert(&Reticle_cur_list, new_rl);
		was_inserted = 1;
	}
	else {
		for ( rl = GET_FIRST(&Reticle_cur_list); rl != END_OF_LIST(&Reticle_cur_list); rl = GET_NEXT(rl) ) {
			if ( !dot_flag ) {

				if ( measure < rl->dist ) {
					list_insert_before(rl, new_rl);
					was_inserted = 1;
					break;
				}
			}
			else {

				if ( measure > rl->dot ) {
					list_insert_before(rl, new_rl);
					was_inserted = 1;
					break;
				}
			}
		}
	}

	if ( !was_inserted ) {
		list_append(&Reticle_cur_list, new_rl);
	}
}
