to_vector ( DataType &val, vector<DataType> &vals, uint32 n, uint32 width ) {
    bitset<1024> bits = to_bitset(val);
    bitset<1024> mask;
    for (uint32 i=0;i<width;++i) mask.set(i);
    do {
       vals.push_back ( (uint32)(bits & mask).to_ulong() );
       bits >>= width;
    } while (--n);
}
