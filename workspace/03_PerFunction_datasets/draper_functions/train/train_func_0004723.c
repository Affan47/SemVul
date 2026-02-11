scrollforward(curr)
int curr;
{
    do {
	writeline(LINES-1, 0, pend+1);
	zwrite("\n", 1);
	pend = fseekeol(pend+1);
	ptop = fseekeol(ptop)+1;
    } while (pend < curr);
}
