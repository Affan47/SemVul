RemoveFromNodeSet( NodeSet *cur_nodes, int k, Vertex v[], int num_v)
{
    if ( cur_nodes->bitword ) {
        bitWord *Bits = cur_nodes->bitword[k];

        int      i, j;

        for ( i = 0; i < num_v; i ++ ) {
            j = (int) v[i];
            Bits[ j / num_bit ] &= ~bBit[ j % num_bit ];
        }
    }
}
