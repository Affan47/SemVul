airDLoad(void *v, int t) {

  switch(t) {
  case airTypeBool:   return AIR_CAST(double,*((int*)v)); break;
  case airTypeInt:    return AIR_CAST(double,*((int*)v)); break;
  case airTypeUInt:   return AIR_CAST(double,*((unsigned int*)v)); break;
  case airTypeLongInt:return AIR_CAST(double,*((long int*)v)); break;
  case airTypeULongInt:return AIR_CAST(double,*((unsigned long int*)v)); break;
  case airTypeSize_t: return AIR_CAST(double, *((size_t*)v)); break;
  case airTypeFloat:  return AIR_CAST(double,*((float*)v)); break;
  case airTypeDouble: return *((double*)v); break;
  case airTypeChar:   return AIR_CAST(double,*((char*)v)); break;
  default: return 0; break;
  }
}
