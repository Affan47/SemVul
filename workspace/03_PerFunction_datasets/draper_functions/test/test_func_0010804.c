print_networks(struct cidr_net **n, int i, int print_name)
{
int k=0;
    if ( !n || !i ) return;
    while( k < i) {
	verb_printf("print_networks(): Net %08x/%-2d[%s]\n", (*n)->network, (*n)->masklen, print_name?(*n)->group->name:"");
	k++; n++;
    }
}
