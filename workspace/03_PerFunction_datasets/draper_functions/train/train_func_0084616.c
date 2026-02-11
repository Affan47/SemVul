get_bond(char base1, char base2) const
{
    int i1 = get_index(base1);
    int i2 = get_index(base2);

    if (i1==-1 || i2==-1) {
        return ' ';
    }
    return bond[i1][i2];
}
