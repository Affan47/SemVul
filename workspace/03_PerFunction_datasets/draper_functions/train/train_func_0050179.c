unpack_bitfields(struct BITS *bits, char name)
{
    switch (name) {
    case 'A': return bits->A;
    case 'B': return bits->B;
    case 'C': return bits->C;
    case 'D': return bits->D;
    case 'E': return bits->E;
    case 'F': return bits->F;
    case 'G': return bits->G;
    case 'H': return bits->H;
    case 'I': return bits->I;

    case 'M': return bits->M;
    case 'N': return bits->N;
    case 'O': return bits->O;
    case 'P': return bits->P;
    case 'Q': return bits->Q;
    case 'R': return bits->R;
    case 'S': return bits->S;
    }
    return 0;
}
