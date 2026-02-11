process_lxt2(char *fname)
{
struct lxt2_rd_trace *lt;

lt=lxt2_rd_init(fname);
if(lt)
	{
	int numfacs;

	numfacs = lxt2_rd_get_num_facs(lt);
	killed_list = calloc(numfacs, sizeof(char));
	lxt2_rd_set_fac_process_mask_all(lt);
	lxt2_rd_set_max_block_mem_usage(lt, 0);

	lxt2_rd_iter_blocks(lt, vcd_callback, NULL);

	lxt2_rd_close(lt);
	free(killed_list);
	}
	else
	{
	fprintf(stderr, "lxt2_rd_init failed\n");
	return(255);
	}

return(0);
}
