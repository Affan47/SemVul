CheckDivide(int nindex1, int indexarray1[],
                    int nindex2, int indexarray2[],
                    int nindex3, int indexarray3[]) const
{
    if (nindex1!=0||nindex2!=0||nindex3!=0)
    {
        outerror(glno, "only scalar is allowed for divide.");
        return -1;
    }
    return 0;
}
