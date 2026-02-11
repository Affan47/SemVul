findCatchBlockInMethod(MethodBlock *mb, Class *exception,
                                CodePntr pc_pntr) {

    ExceptionTableEntry *table = mb->exception_table;
    int size = mb->exception_table_size;
    int pc = pc_pntr - ((CodePntr)mb->code);
    int i;

    for(i = 0; i < size; i++)
        if((pc >= table[i].start_pc) && (pc < table[i].end_pc)) {


            if(table[i].catch_type != 0) {
                Class *caught_class = resolveClass(mb->class,
                                                   table[i].catch_type,
                                                   TRUE, FALSE);
                if(caught_class == NULL) {
                    clearException();
                    continue;
                }
                if(!isInstanceOf(caught_class, exception))
                    continue;
            }
            return ((CodePntr)mb->code) + table[i].handler_pc;
        }

    return NULL;
}
