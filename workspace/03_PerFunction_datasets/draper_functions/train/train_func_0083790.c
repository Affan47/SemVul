handle_memory_free()
{
 FUNC_NAME;


 DECLARE_PROCESS_ID_STR(proc_id, CUR_INDEX);
 size_t block_size = GET_PARAM(CUR_EV, 1);


 DECLARE_CUR_PROCESS(p_process);
 INIT_MEMORY_PROCESS_INFO(p_process, p_mem);

 p_mem->nb_free++;
 if( p_mem->memory_use >= block_size)
   p_mem->memory_use -= block_size;
 else {
   fprintf(stderr, "t=%lf\tWarning: %s frees %ld bytes, but only %ld are currently allocated\n",
	   CURRENT, CUR_ID, block_size, p_mem->memory_use);
   p_mem->memory_use = 0;
 }

 p_mem->total_freed += block_size;

 MEMORY_CHANGE() setVar(CURRENT, "V_Mem", proc_id, p_mem->memory_use);
}
