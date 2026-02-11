FuncELM0_LIST (
    Obj                 self,
    Obj                 list,
    Obj                 pos )
{
    Obj                 elm;
    elm = ELM0_LIST( list, INT_INTOBJ(pos) );
    if ( elm == 0 ) {
        return Fail;
    }
    else {
        return elm;
    }
}
