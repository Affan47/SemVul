adj_escape_prob(U16B esc, U16B cp) {

    if (ft[cp]==1) return iec[cl[cp]]>=(IECLIM>>1)?2:1;
    if (cc[cp]==255) return 1;
    if (cc[cp] && ((cc[cp]+1)<<1)>=ft[cp]) {
	esc=(S16B)((S32B)esc*((cc[cp]+1)<<1)/ft[cp]);
	if (cc[cp]+1==ft[cp]) esc+=(cc[cp]+1)>>1;
    }
    return esc?esc:1;
}
