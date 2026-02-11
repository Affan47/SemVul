sortTetra( uchar4 t , IntType* i )
  {
#define SWAP(a,b) { IntType tmp=a; a=b; b=tmp; }
    if( i[t.y] < i[t.x] ) SWAP(t.x,t.y);
    if( i[t.w] < i[t.z] ) SWAP(t.z,t.w);
    if( i[t.z] < i[t.y] ) SWAP(t.y,t.z);
    if( i[t.y] < i[t.x] ) SWAP(t.x,t.y);
    if( i[t.w] < i[t.z] ) SWAP(t.z,t.w);
    if( i[t.z] < i[t.y] ) SWAP(t.y,t.z);
#undef SWAP
    return t;
  }
