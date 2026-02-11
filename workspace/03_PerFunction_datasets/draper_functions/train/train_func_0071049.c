mdb_midl_sort( IDL ids )
{

	int istack[sizeof(int)*CHAR_BIT * 2];
	int i,j,k,l,ir,jstack;
	ID a, itmp;

	ir = ids[0];
	l = 1;
	jstack = 0;
	for(;;) {
		if (ir - l < SMALL) {
			for (j=l+1;j<=ir;j++) {
				a = ids[j];
				for (i=j-1;i>=1;i--) {
					if (ids[i] >= a) break;
					ids[i+1] = ids[i];
				}
				ids[i+1] = a;
			}
			if (jstack == 0) break;
			ir = istack[jstack--];
			l = istack[jstack--];
		} else {
			k = (l + ir) >> 1;
			SWAP(ids[k], ids[l+1]);
			if (ids[l] < ids[ir]) {
				SWAP(ids[l], ids[ir]);
			}
			if (ids[l+1] < ids[ir]) {
				SWAP(ids[l+1], ids[ir]);
			}
			if (ids[l] < ids[l+1]) {
				SWAP(ids[l], ids[l+1]);
			}
			i = l+1;
			j = ir;
			a = ids[l+1];
			for(;;) {
				do i++; while(ids[i] > a);
				do j--; while(ids[j] < a);
				if (j < i) break;
				SWAP(ids[i],ids[j]);
			}
			ids[l+1] = ids[j];
			ids[j] = a;
			jstack += 2;
			if (ir-i+1 >= j-1) {
				istack[jstack] = ir;
				istack[jstack-1] = i;
				ir = j-1;
			} else {
				istack[jstack] = j-1;
				istack[jstack-1] = l;
				l = i;
			}
		}
	}
}
