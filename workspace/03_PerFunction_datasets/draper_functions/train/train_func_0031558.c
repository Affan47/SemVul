chr_cnt FCN((s,c))
outer_char*s C0("String to be searched for occurrences of |c|")
outer_char c C1("Search character")
{
int n;

for(n= 0;*s;s++)
if(*s==c)
n++;

return n;
}
