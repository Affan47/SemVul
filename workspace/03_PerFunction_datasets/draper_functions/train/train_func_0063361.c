doins(flag)
bool flag;
{
    int i;
    curr = low;
    exprintln();
    low = insertion(1,setstep[flag],&i,&i,NO)-1;
    if (low >= 0)
	curr = low;
    diddled = YES;
}
