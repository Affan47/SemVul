mcos(const N a, N b)
{
     N a2, g, k;
     int i;

     cpy(i32fac, g);
     cpy(g, b);
     mul(a, a, a2);


     for (i = 32; i > 0; i -= 2) {
	  fromshort(i * (i - 1), k);
	  mul(k, g, g);
	  mul(a2, b, k);
	  sub(g, k, b);
     }
}
