leave_l_mod_call_list(l_mod_call_list_t *l_list)
{
mod_call_t      *this, *next;

    if ( l_list ) {
	pthread_mutex_lock(&l_list->lock);
	if ( (l_list->refs == 1) ) {
		pthread_mutex_destroy(&l_list->lock);
                this = l_list->list;
                while(this) {
                    next = this->next;
                    free(this);
                    this = next;
                }
		free(l_list);
	} else {
	    l_list->refs--;
	    pthread_mutex_unlock(&l_list->lock);
	}
    }
}
