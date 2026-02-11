flipUDIFChecksum(UDIFChecksum* o, char out) {
  int i;

  FLIPENDIAN(o->type);

  if(out) {
    for(i = 0; i < o->size; i++) {
      FLIPENDIAN(o->data[i]);
    }
    FLIPENDIAN(o->size);
  } else {
    FLIPENDIAN(o->size);
    for(i = 0; i < o->size; i++) {
      FLIPENDIAN(o->data[i]);
    }
  }
}
