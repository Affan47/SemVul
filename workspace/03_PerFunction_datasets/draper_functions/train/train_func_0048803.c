node(int x, int l, int r)
{
    if(line >= MAXLIN)
	overflo();
    name[line] = x;
    left[line] = l;
    right[line] = r;
    parent[l] = line;
    parent[r] = line;
    return(line++);
}
