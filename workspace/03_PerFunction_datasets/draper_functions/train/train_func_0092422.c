vzt_rd_close(struct vzt_rd_trace *lt)
{
if(lt)
	{
	struct vzt_rd_block *b, *bt;

	if(lt->process_mask) { free(lt->process_mask); lt->process_mask=NULL; }

	if(lt->rows) { free(lt->rows); lt->rows=NULL; }
	if(lt->msb) { free(lt->msb); lt->msb=NULL; }
	if(lt->lsb) { free(lt->lsb); lt->lsb=NULL; }
	if(lt->flags) { free(lt->flags); lt->flags=NULL; }
	if(lt->len) { free(lt->len); lt->len=NULL; }
	if(lt->vindex_offset) { free(lt->vindex_offset); lt->vindex_offset=NULL; }
	if(lt->zfacnames) { free(lt->zfacnames); lt->zfacnames=NULL; }

	if(lt->value_current_sector) { free(lt->value_current_sector); lt->value_current_sector=NULL; }
	if(lt->value_previous_sector) { free(lt->value_previous_sector); lt->value_previous_sector=NULL; }

	if(lt->faccache)
		{
		if(lt->faccache->bufprev) { free(lt->faccache->bufprev); lt->faccache->bufprev=NULL; }
		if(lt->faccache->bufcurr) { free(lt->faccache->bufcurr); lt->faccache->bufcurr=NULL; }

		free(lt->faccache); lt->faccache=NULL;
		}

	b=lt->block_head;
	while(b)
		{
		bt=b->next;
		vzt_rd_block_vch_free(lt, b, 1);
		vzt_rd_pthread_mutex_destroy(lt, &b->mutex);

		free(b);
		b=bt;
		}

	lt->block_head=lt->block_curr=NULL;

	if(lt->zhandle) { gzclose(lt->zhandle); lt->zhandle=NULL; }
	if(lt->handle) { fclose(lt->handle); lt->handle=NULL; }
	if(lt->filename) { free(lt->filename); lt->filename=NULL; }

	vzt_rd_pthread_mutex_destroy(lt, &lt->mutex);

	free(lt);
	}
}
