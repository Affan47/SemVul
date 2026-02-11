multi_join_cull_timeouts()
{
	active_game *backup;
	int count;
	active_game *moveup = Active_game_head;


	count = 0;
	if(moveup != NULL){
		do {
			if((moveup->heard_from_timer != -1) && (timestamp_elapsed(moveup->heard_from_timer))){
				Active_game_count--;


				if(moveup == Active_game_head){

					if(moveup->next == Active_game_head){

						multi_join_handle_item_cull(Active_game_head, count);

						vm_free(Active_game_head);
						Active_game_head = NULL;
						return;
					}

					else {

						multi_join_handle_item_cull(moveup, count);

						Active_game_head = moveup->next;
						Active_game_head->prev = moveup->prev;
						Active_game_head->prev->next = Active_game_head;
						vm_free(moveup);
						moveup = Active_game_head;
					}
				}

				else {

					multi_join_handle_item_cull(moveup, count);


					moveup->next->prev = moveup->prev;
					moveup->prev->next = moveup->next;


					if(moveup->next == Active_game_head){
						vm_free(moveup);
						return;
					} else {
						backup = moveup->next;
						vm_free(moveup);
						moveup = backup;
					}
				}
			} else {
				moveup = moveup->next;
				count++;
			}
		} while(moveup != Active_game_head);
	}
}
