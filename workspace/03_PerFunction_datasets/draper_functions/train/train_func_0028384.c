handle_memory_realloc()
{
 FUNC_NAME;


 DECLARE_PROCESS_ID_STR(proc_id, CUR_INDEX);
 int old_size = GET_PARAM(CUR_EV, 1);
 int new_size = GET_PARAM(CUR_EV, 2);


 DECLARE_CUR_PROCESS(p_process);
 INIT_MEMORY_PROCESS_INFO(p_process, p_mem);

 p_mem->nb_malloc++;
 p_mem->nb_free++;
 p_mem->memory_use += new_size - old_size;
 p_mem->total_malloced += new_size - old_size;

 if(p_mem->memory_use > p_mem->max_mem_used)
   p_mem->max_mem_used = p_mem->memory_use;

 MEMORY_CHANGE() setVar(CURRENT, "V_Mem", proc_id, p_mem->memory_use);
}
