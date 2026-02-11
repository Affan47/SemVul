generic_table(unsigned int *value, const unsigned int lng, const int algo,const unsigned int val_stop,const int mode_aff)
{
  {
    unsigned int i;
    for(i=0;i<lng;i++)
      if(value[i]==val_stop && algo!=ALGO_COMPAQ)
	value[i]=VAL_STOP;
  }
  switch(algo)
  {
    case ALGO_AMI_F0:
    case ALGO_AMI:
    case ALGO_AMI_80:
      generic_ami(value,lng,algo);
      break;
    case ALGO_UNKNOW:
      generic_unknown(value,lng);
      break;
    case ALGO_ACER:
      generic_acer(value,lng);
      break;
    case ALGO_AWARD6:
      generic_award6(value,lng);
      break;
    case ALGO_PACKARD:

      generic_packard(value,lng);
      break;
    case ALGO_NONE:
      break;
    case ALGO_PHOENIX_DEC:
      generic_phoenix_dec(value,lng);
      break;
    case ALGO_PHOENIX_XOR:
      generic_phoenix_xor(value,lng);
      break;
    case ALGO_PHOENIX_ADD:
      generic_phoenix_add(value,lng);
      break;
    case ALGO_DTK:
      generic_dtk(value,lng);
      break;
    case ALGO_COMPAQ:
      generic_compaq(value,lng);
      break;
    default:
      printf("BAD ALGO ");
      return;
  }
  if(mode_aff==AFF_SCAN)
    convert_scancode2ascii(value,lng);
  aff_result(value,lng);
}
