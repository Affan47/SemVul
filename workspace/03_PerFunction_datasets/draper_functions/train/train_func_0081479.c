immnum_le(object x,object y) {return (((ufixnum)(((ufixnum)x)&((ufixnum)y)))>=0x8000000000000000) ? (x <= y) : (number_compare(x,y) <= 0);}
