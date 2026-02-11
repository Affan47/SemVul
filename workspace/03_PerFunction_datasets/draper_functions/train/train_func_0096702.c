op_operands(enum prog_opcode opcode)
{
   int i;


   for(i=0; i < sizeof(op_names) / sizeof(*op_names); i++)
      if(op_names[i].opcode == opcode)
	 return op_names[i].ip;

   fprintf(stderr, "op %d not found in op_names\n", opcode);
   exit(-1);
   return 0;
}
