FindSubs(
                Obj        tree,
                Int        x,
                Obj        list1,


                Obj        list2,


                Obj        a,


                Obj        b,

                Int        al,
                Int        ar,
                Int        bl,
                Int        br,
                Obj        reps,
                Obj        pr,
                Obj        max
                                        )
{
   Int    i;


   if (  al > ar  ||  bl > br  )
   {


       SetSubs( list1, a, tree);
       SetSubs( list2, b, tree);
       FindNewReps(tree, reps, pr, max);
       return;
   }


   if ( INT_INTOBJ( DT_MAX(tree, x) ) <= 0  ||
        ELM_PLIST(a, ar) < DT_MAX(tree, x)   )
   {
       for (i=al; i<=ar; i++)
           SET_ELM_PLIST(a, i, INTOBJ_INT( CELM(a,i) + 1 ) );
       FindSubs(tree, x, list1, list2, a, b, al, ar, bl+1, br, reps, pr, max);
       for  (i=al; i<=ar; i++)
           SET_ELM_PLIST(a, i, INTOBJ_INT( CELM(a, i) - 1  ) );
   }
   FindSubs(tree, x, list1, list2, a, b, al+1, ar, bl+1, br, reps, pr, max);


   if ( INT_INTOBJ( DT_MAX(tree, x) ) <= 0  ||
        ELM_PLIST(b, br) < DT_MAX(tree, x)        )
   {
       for  (i=bl; i<=br; i++)
           SET_ELM_PLIST(b, i, INTOBJ_INT( CELM(b, i) + 1  ) );
       FindSubs(tree, x, list1, list2, a, b, al+1, ar, bl, br, reps, pr, max);
       for  (i=bl; i<=br; i++)
           SET_ELM_PLIST(b, i, INTOBJ_INT( CELM(b, i) - 1 ) );
   }
}
