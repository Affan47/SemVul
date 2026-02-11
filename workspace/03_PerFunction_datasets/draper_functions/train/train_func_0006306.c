t1_Scale(obj, sx, sy)
       struct xobject *obj;
       DOUBLE sx,sy;
{
       DOUBLE M[2][2];
       IfTrace3((MustTraceCalls),"Scale(%p, %f, %f)\n", obj, sx, sy);
       M[0][0] = sx;
       M[1][1] = sy;
       M[1][0] = M[0][1] = 0.0;
       ConsiderContext(obj, M);
       return(Xform(obj, M));
}
