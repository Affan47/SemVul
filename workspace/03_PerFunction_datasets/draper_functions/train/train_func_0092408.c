outshow(void)
{

    outflag = 1;


    if (dbghid && hidout)
    {
        hidout = 0;
        trcsho();
    }


    return outcnt;
}
