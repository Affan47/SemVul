save_state(FILE *fp)
{

  if(!fp)
    return;

  unsigned int i;

  fprintf(fp,"PROCESSOR:%s\n",name().c_str());

  for(i=1; i<register_memory_size(); i++) {

    Register *reg = rma.get_register(i);

    if(reg && reg->isa() != Register::INVALID_REGISTER) {

      fprintf(fp,"R:%X:%s:(%X,%X)\n",
              reg->address,
              reg->name().c_str(),
              reg->value.get(),
              reg->value.geti());

    }
  }
  if(pc)
    fprintf(fp,"P:0:PC:%X\n",pc->value);
}
