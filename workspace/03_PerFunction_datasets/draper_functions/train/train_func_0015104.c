vzt_rd_value(struct vzt_rd_trace *lt, vztint64_t simtime, vztint32_t idx)
{
struct vzt_rd_block *b, *b2;
char *rcval = NULL;

if(lt)
	{
	b = lt->block_head;

	if((simtime == lt->last_rd_value_simtime) && (lt->last_rd_value_block))
		{
		b = lt->last_rd_value_block;
		goto b_chk;
		}
		else
		{
		lt->last_rd_value_simtime = simtime;
		}

	while(b)
		{
		if((b->start > simtime) || (b->end < simtime))
			{
			b = b->next;
			continue;
			}

		lt->last_rd_value_block = b;
b_chk:		if((!b->mem)&&(!b->short_read_ignore))
			{
			vzt_rd_decompress_blk(lt, b, 0);
			}

		if(b->mem)
			{
			rcval = vzt_rd_process_block_single_factime(lt, b, simtime, idx);
			break;
			}

		b=b->next;
		}
	}
	else
	{
	return(NULL);
	}

if((b)&&(lt->numblocks > 2))
	{
	vztint64_t block_mem_consumed;

	vzt_rd_pthread_mutex_lock(lt, &lt->mutex);
	block_mem_consumed = lt->block_mem_consumed;
	vzt_rd_pthread_mutex_unlock(lt, &lt->mutex);

	if(block_mem_consumed > lt->block_mem_max)
		{
		b2 = lt->block_head;
		while(b2)
			{
			if((block_mem_consumed > lt->block_mem_max) && (b2 != b))
				{
				vzt_rd_pthread_mutex_lock(lt, &lt->mutex);
				lt->block_mem_consumed -= b2->uncompressed_siz;
				vzt_rd_pthread_mutex_unlock(lt, &lt->mutex);
				vzt_rd_block_vch_free(lt, b2, 0);
				}

			b2 = b2->next;
			}
		}
	}

return(rcval);
}
