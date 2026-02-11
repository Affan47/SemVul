Find(const R2 & P) const
 {


    for (int i=0;i<nt;i++)
     {
      kthrough++;
      const Triangle & K(triangles[i]);
      R2 A(K[0]),B(K[1]),C(K[2]);
      R a=Area2(P,B,C);
      R b=Area2(A,P,C);
      R c=Area2(A,B,P);
      R s=a+b+c;
      R eps=s*1e-6;
      if (a>-eps && b >-eps && c >-eps) return triangles + i;

     }
   return 0;
 }
