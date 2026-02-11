t1_Loc(S, x, y)
       register struct XYspace *S;
       DOUBLE x,y;
{
       register struct segment *r;


       IfTrace3((MustTraceCalls),"..Loc(S=%p, x=%f, y=%f)\n", S, x, y);

       r = (struct segment *)Allocate(sizeof(struct segment), &movetemplate, 0);
       TYPECHECK("Loc", S, SPACETYPE, r, (0), struct segment *);

       r->last = r;
       r->context = S->context;
       (*S->convert)(&r->dest, S, x, y);
       ConsumeSpace(S);
       return(r);
}
