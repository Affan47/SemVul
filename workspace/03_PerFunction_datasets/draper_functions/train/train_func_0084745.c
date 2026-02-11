alloc_dataflow_info(void)
{
    DataflowInfo *ptr = NULL;

    ptr = (DataflowInfo *)calloc(1, sizeof(DataflowInfo));

    if(ptr == NULL){
	fatal("No more room for DataflowInfo.\n");
    }

    return(ptr);
}
