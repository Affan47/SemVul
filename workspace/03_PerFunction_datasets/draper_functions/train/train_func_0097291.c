FuncAddAbelianRelator (
    Obj                 self,
    Obj                 rels,
    Obj                 number )
{
    Obj *               ptRels;
    Obj *               pt1;
    Obj *               pt2;
    Obj                 tmp;
    Int                 numcols;
    Int                 numrows;
    Int                 i, j;


    if ( ! IS_PLIST(rels) ) {
        ErrorQuit( "<rels> must be a plain list (not a %s)",
            (Int)TNAM_OBJ(rels), 0L );
        return 0;
    }
    ptRels = &(ELM_PLIST(rels,1)) - 1;
    if ( TNUM_OBJ(number) != T_INT ) {
        ErrorQuit( "<number> must be a small integer (not a %s)",
            (Int)TNAM_OBJ(number), 0L );
        return 0;
    }


    numrows = INT_INTOBJ(number);
    if ( numrows < 1 || LEN_PLIST(rels) < numrows ) {
        ErrorQuit( "inconsistent relator number", 0L, 0L );
        return 0;
    }
    tmp = ELM_PLIST( rels, numrows );
    if ( tmp == 0 ) {
        ErrorQuit( "inconsistent relator number", 0L, 0L );
        return 0;
    }
    pt2 = &(ELM_PLIST(tmp,1)) - 1;


    numcols = LEN_PLIST(tmp);


    for ( i = 1;  i <= numcols;  i++ ) {
        if ( INT_INTOBJ(pt2[i]) ) {
            break;
        }
    }
    if ( i > numcols ) {
        return INTOBJ_INT(numrows-1);
    }


    if ( INT_INTOBJ(pt2[i]) < 0 ) {
        for ( j = i;  j <= numcols;  j++ ) {
            pt2[j] = INTOBJ_INT( -INT_INTOBJ( pt2[j] ) );
        }
    }


    for ( i = 1;  i < numrows;  i++ ) {
        pt1 = &(ELM_PLIST(ptRels[i],1)) - 1;
        for ( j = 1;  j <= numcols;  j++ ) {
            if ( pt1[j] != pt2[j] ) {
                break;
            }
        }
        if ( j > numcols ) {
            break;
        }
    }
    if ( i < numrows ) {
        for ( i = 1;  i <= numcols;  i++ ) {
            pt2[i] = INTOBJ_INT(0);
        }
        numrows = numrows - 1;
    }

    return INTOBJ_INT( numrows );
}
