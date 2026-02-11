vitem(vari* v, int i)
{
    int index;
    if ((v==NULL) || (vlength(v)==0))
        return(0.0);
    index = i % vlength(v);
    switch(v->mode)
    { case VDOUBLE: return( vdptr(v)[index] );
        case VINT:
        { INT *z;
            z = (INT *)vdptr(v);
            return(z[index]);
        }
        case VCHAR:
        { char *z;
            z = (char *)vdptr(v);
            return(z[index]);
        }
    }
    ERROR(("Invalid mode in vitem()"));
    return(0.0);
}
